`timescale 1ns / 1ps
/************************************************************************/
 /* Last modified in 4/29/2024
/************************************************************************/

module main_audio_controller (

    input BTNC,
    input CLK100MHZ, 
    inout scl,
    inout sda,
    output ac_mclk,
    input  ac_adc_sdata,
    output  ac_dac_sdata,
    output ac_bclk,
    output ac_lrclk,
    output   [14:0] ddr3_addr,
    output   [2:0] ddr3_ba,
    output   ddr3_ras_n,
    output   ddr3_cas_n,
    output   ddr3_reset_n,
    output   ddr3_we_n,
    output   ddr3_ck_p,
    output   ddr3_ck_n,
    output   ddr3_cke,
    output   [1:0] ddr3_dm,
    output   ddr3_odt,
    inout    [15:0] ddr3_dq,
    inout    [1:0] ddr3_dqs_p,
    inout    [1:0] ddr3_dqs_n
);

   wire clk50;
    parameter tenhz = 10000000;

    wire [4:0] buttons_i;
    assign buttons = BTNC;
   
   
    wire [15:0]r;//Bank is recording
    wire [3:0] mem_bank;//Ba
    wire [21:0]current_block;//Block address
    wire [4:0] buttons_db;//Debounced buttons
    wire [15:0] active;//Bank is recorded on
    
    wire [3:0] current_bank;
    
    wire [25:0] mem_a;
    assign mem_a = {current_block,mem_bank}; 
    wire [63:0] mem_dq_i;
    wire [63:0] mem_dq_o;
    reg [63:0] mem_dq_o_b;
    wire mem_cen;
    wire mem_oen;
    wire mem_wen;

    wire [15:0] display;
    wire data_flag;
    reg [23:0] sound_dataL;
    reg [23:0] sound_dataR;
    wire data_ready;
    
    wire mix_data;
    wire [21:0] block48KHz;
    
    wire clk_out_100MHZ;
    wire clk_out_200MHZ;
    
   
    clk_wiz_0 clk_1
    (
        .clk_in1(CLK100MHZ),
        .clk_out1(clk_out_100MHZ),
        .clk_out2(clk_out_200MHZ),
        .clk_out3(ac_mclk),
        .clk_out4(clk50),   
        .locked()            
    );     

//////////////////////////////////////////////////////////////////////////////////////////////////////////
////    Audio Initialization via TWI
////////////////////////////////////////////////////////////////////////////////////////////////////////// 

    audio_init initialize_audio
    (
        .clk(clk50),
        .rst(rst),
        .sda(sda),
        .scl(scl)
    );


    wire[23:0] mixL;
    wire[23:0] mixR;
    wire[15:0] play;//Bank is playing
  


////////////////////////////////////////////////////////////////////////////////////////////////////////
////    Sound control
////////////////////////////////////////////////////////////////////////////////////////////////////////

    debounce dbuttons(
        .clock(clk_out_100MHZ),
        .reset(rst),
        .button(buttons_i),
        .out(buttons_db)
    );

////////////////////////////////////////////////////////////////////////////////////////////////////////
////    Memory //////////////////////////////////////////////////////////////////////////////////////////////////////// 

wire read_data_valid;
reg read_data_valid_d1;
reg read_data_valid_d2;
wire read_data_valid_rise;
always @ (posedge(clk_out_100MHZ))begin
    read_data_valid_d1<=read_data_valid;
    read_data_valid_d2<=read_data_valid_d1;
end
assign read_data_valid_rise = read_data_valid_d1 & ~read_data_valid_d2;

    DDRcontrol Ram(
        .clk_200MHz_i          (clk_out_200MHZ),
        .rst_i                 (rst),
        // RAM interface
        .ram_a                 (mem_a),
        .ram_dq_i              (mem_dq_i),
        .ram_dq_o              (mem_dq_o),
        .ram_cen               (mem_cen),
        .ram_oen               (mem_oen),
        .ram_wen               (mem_wen),
        .data_valid            (read_data_valid),
          // ddr3 interface
        .ddr3_addr             (ddr3_addr),
        .ddr3_ba               (ddr3_ba),
        .ddr3_ras_n            (ddr3_ras_n),
        .ddr3_cas_n            (ddr3_cas_n),
        .ddr3_reset_n          (ddr3_reset_n),
        .ddr3_we_n             (ddr3_we_n),
        .ddr3_ck_p             (ddr3_ck_p),
        .ddr3_ck_n             (ddr3_ck_n),
        .ddr3_cke              (ddr3_cke),
        .ddr3_dm               (ddr3_dm),
        .ddr3_odt              (ddr3_odt),
        .ddr3_dq               (ddr3_dq),
        .ddr3_dqs_p            (ddr3_dqs_p),
        .ddr3_dqs_n            (ddr3_dqs_n)
    );
          
////////////////////////////////////////////////////////////////////////////////////////////////////////
////    Memory Controller
//////////////////////////////////////////////////////////////////////////////////////////////////////// 
    reg pulse48kHz;
    reg[3:0] lrclkcnt=0;
    
    always@(posedge(clk_out_100MHZ))begin
        if (lrclkcnt==8)begin
            pulse48kHz<=1;
            lrclkcnt<=0;
            end
        else
            pulse48kHz<=0;
    end


    mem_ctrl mem_controller(
        .clk_100MHz(clk_out_100MHZ),
        .rst(rst),
        .pulse(pulse48kHz),
        
        .playing(play),
        .recording(r),
        .read_data_valid(read_data_valid_rise),
        .max_block(16),
        .delete_clear(del_mem),
        .RamCEn(mem_cen),
        .RamOEn(mem_oen),
        .RamWEn(mem_wen),
        .write_zero(write_zero),
        .get_data(data_flag),
        .data_ready(data_ready),
        .mix_data(mix_data),
        
        .addrblock48khz(block48KHz),
        .mem_block_addr(current_block),
        .mem_bank(mem_bank));
        
    assign mem_dq_i = (write_zero==1) ?  64'h0000000000000000 :  {16'h0000, sound_dataL[23:0], sound_dataR[23:0]};

    always@(posedge(clk_out_100MHZ))begin
        mem_dq_o_b<=mem_dq_o;
    end

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Audio input 
////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    wire [23:0] in_audioL;
    wire [23:0] in_audioR;
    wire [23:0] out_audioL;
    wire [23:0] out_audioR;
    
        
    i2s_ctl audio_inout(
        .CLK_I(clk_out_100MHZ),    //Sys clk
        .RST_I(rst),    //Sys rst
        .EN_TX_I(1),  // Transmit Enable (push sound data into chip)
        .EN_RX_I(1), //Receive enable (pull sound data out of chip)
        .FS_I(4'b0101),     //Sampling rate selector
        .MM_I(0),     //Audio controller Master mode select
        .D_L_I(mixL),    //Left channel data input from mix (mixed audio output)
        .D_R_I(mixR),   //Right channel data input from mix
        .D_L_O(in_audioL),    // Left channel data (input from mic input)
        .D_R_O(in_audioR),    // Right channel data (input from mic input)
        .BCLK_O(ac_bclk),   // serial CLK
        .LRCLK_O(ac_lrclk),  // channel CLK
        .SDATA_O(ac_dac_sdata),  // Output serial data
        .SDATA_I(ac_adc_sdata)   // Input serial data
    ); 
     
    reg lrclkD1=0;
    reg lrclkD2=0;
    
    always@(posedge(clk_out_100MHZ))begin
        lrclkD1<=ac_lrclk;
        lrclkD2<=lrclkD1;
    end
    

////////////////////////////////////////////////////////////////////////////////////////////////////////
////    Data in latch
//////////////////////////////////////////////////////////////////////////////////////////////////////// 

    //Latch audio data input when data_flag goes high
    always@(posedge(clk_out_100MHZ))begin 
        if (data_flag==1)begin
            sound_dataL<=in_audioL;
            sound_dataR<=in_audioR;
        end
    end
 
 
endmodule


/*************************************/

/* Last Modified: April 29 2024 

/****************************************/


module memory_interface (
    input clk,
    input [15:0] playing,
    input [15:0] recording,
    input valid,
    input pulse,   
    output reg RamCEn,
    output reg RamOEn,
    output reg RamWEn,
    output reg write_zero,
    output reg get_data,
    output reg data_ready,
    output reg [21:0] address,
    output [21:0] block_addr,
    output reg [3:0] bank

);    


    parameter BANK = 4'b0000;
    parameter FLAG = 4'b0001;
    parameter WRITE_BACK = 4'b0010;
    parameter INC_BLOCK = 4'b0011;
    parameter WAIT = 4'b0100;
    parameter READ_BACK = 4'b1000;
    
    wire address_enable;
    assign address_enable = playing || recording;
    reg [12:0] count=0;
    reg [4:0]pstate = WAIT;
    reg [3:0] nstate = BANK;
    reg delay_done = 0;
    reg counterEnable=0;
    reg increment=0;
    integer counter = 0;
    reg [21:0] max_delete_block=0;
    reg [21:0] delete_address=0;
    reg WEn_d1=1;

    assign block = (write_zero==0) ? address : delete_address;

always @ (posedge(clk)) begin
    if (address_enable==0)address<=0;
    else if(increment==1)begin
        if(block==0 || address < 16)
            address <= address + 1;
        else
            address <= 0;
    end
end
    
always @(posedge(clk))begin
    RamWEn<=WEn_d1;
end
    
always @ (posedge clk)
begin
    case (pstate)
        BANK : begin
            if(bank==15)nstate<=INC_BLOCK;
            else nstate <= BANK;  
            if(recording[bank] == 1)begin
                get_data <= 1;
                counterEnable <= 1;
                RamCEn<=0;
                RamOEn<=1;
                WEn_d1<=0;
                pstate<=WRITE_BACK;
            end
            else if(playing[bank] == 1)begin
                get_data<=0;
                RamCEn <= 0;
                RamOEn <= 0;
                WEn_d1 <= 1;
                pstate<=READ_BACK;
            end
            else begin
                get_data<=0;
                RamCEn <= 1;
                RamOEn <= 1;
                WEn_d1 <= 1;
                data_ready <= 1;
                pstate <= FLAG;
            end            
        end
        FLAG : begin
            data_ready <= 0;
            if(bank !=15)bank <= bank + 1;//Increment bank by 1 after data_ready pulse
            pstate <= nstate;
        end
        READ_BACK : begin
            if (valid)begin
                data_ready<=1;
                RamCEn<=1;
                RamOEn<=1;
                WEn_d1<=1;
                pstate <= FLAG;
                counterEnable <= 0;
            end
        end
        
        WRITE_BACK : begin
            get_data<=0;
            if (counter==60)begin 
                data_ready<=1;
                RamCEn<=1;
                RamOEn<=1;
                WEn_d1<=1;
            end
            else data_ready<=0;
            if(delay_done == 1)begin 
                pstate <= nstate;
                bank<=bank+1;
                counterEnable <= 0;
             end
        end
        
        INC_BLOCK: begin
            increment <= 1;
            nstate <= WAIT;
            pstate <= WAIT;
        end
        
        WAIT: begin
            increment <= 0;
            bank<=0;
            if(pulse == 1)begin
                pstate <= BANK;
            end else 
                pstate <= WAIT;
            end
    endcase
   end      
 
 always @(posedge clk)begin
    if(counterEnable==0)begin
        counter <= 0;
        delay_done <= 0;
    end
    else if(counter < 62) begin
        counter <= counter + 1;
        delay_done <= 0;
    end
    
    else begin
        counter <= 0;
        delay_done <= 1;
    end
   end       
endmodule

