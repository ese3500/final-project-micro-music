`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/2024
// Design Name:  audio_box
// Module Name: playback
// Project Name: Differentiated Audio Box 
// Target Devices: xc7a200tsbg484-L
// Tool Versions: 
// Description: creating a light weight IP that is goihng to sample sound, process it, store it in memory
// and playback. 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module playback(
    input BTNC, 
    input clk, 
    input rst_n,  
    inout serial_clk, 
    inout serial_data, 
    
    output audio_codec_chip_master_clk, 
    
    output dac_serial_data, 
    input adc_serial_data, 
    output audio_bit_clk, 
    output lr_clk, //left or right clock 
    
    //Memory  signals
    
    output [14:0] address_ddr3, //address line for accessing memory on the DDR3 memory
    output [2:0] bank_address_ddr3, //Bank address for selecting specific memory within the DDR3
    output rbank_address_strobe_n, //Row address strobe 
    output cbanck_address_strobe_n, //Column address strobe
    output reset_ddr3_n, //Reset signal for the DDR3 memory controller 
    output we_ddr3_n, //Write enable (active low)
    output clk_ddr3_p, 
    output clk_ddr3_n, 
    output enable_clk, 
    output [1:0] data_mask_ddr3, 
    output on_die_termination_ddr3, 
    inout [15:0] databus_ddr3, 
    inout [1:0] strobe_signal_p, //positive strobe signal (for data alignment)
    inout [1:0] strobe_signal_n //negative strobe signal (for data alignment)
    );
    
    wire rst; 
    assign rst = ~rst_n;
    
    parameter tenMHz = 10000000; 
    
    assign button = BTNC; 
    
    wire [15:0] recording; 
    wire [12:0] block_address; 
    wire [15:0] active; //Recorded bank on
    wire [3:0] bank_memory; 
    
    wire [3:0] bank_address;
    wire [25:0] memory_address = {bank_address, bank_memory}; 
    
    //memory address = block_address * 8 + bank_number
    wire [63:0] data_input_memory; 
    wire [63:0] data_output_memory; 
    wire [63:0] data_output_buffer_memory;
    wire chip_enable_memory; 
    wire write_enable_memory; 
   
    
    wire data_flag; 
    reg [23:0] sound_dataL; 
    reg [23:0] sound_dataR; 
    wire data_ready;
    
    
    wire mixed_audio_ouput; 
    wire [21:0] audio_data_48KHz; 
    wire clk_100MHz; 
    wire clk_200MHz;
    wire clk_50MHz; 
    
    
    /* 
        Instantiating CLK
    */
    
    clock_gen clock_gen_i
       (.clk_in1(clk),
        .clk_out1(clk_100MHz),
        .clk_out2(clk_200MHz),
        .clk_out3(audio_codec_chip_master_clk),
        .clk_out4(clk_50MHz),
        .locked(locked));
        
    /*
        Initialized audio 
    */
    
    audio initialize_audio (
        .clk(clk_50MHz), 
        .rst(rst), 
        .serial_clk(serial_clk), 
        .serial_data(serial_data)
    );
    
    wire[15:0] play; 
    wire debounced_button; 
    
    debounce_module button_db (
        .clk(clk), 
        .rst(rst), 
        .button(button), 
        .out_button(debounced_button)
        );
       
    
    wire read_data_valid; 
    reg d1_read_data_valid; 
    reg d2_read_data_valid;
    wire rise_read_data_valid; 
    
    always @(posedge clk) begin 
        d1_read_data_valid <= read_data_valid; 
        d2_read_data_valid <= d1_read_data_valid; 
    end
    
    assign read_data_valid_rise = d1_read_data_valid & ~d2_read_data_valid; 
    
    
    control main(
      .clk(clk),
      .rst(rst),
      .btn(debounced_button), 
      .play(play), 
      .recording(recording), 
      .active(active),
      .bank_address(bank_address), 
      .block_address(block_address)
      );
      
      
      
      /* 
        Memory instantiation 
      */
      
    DDR3 DRAM(
        .clk (clk_200MHz), 
        .rst(rst),
        .address_ddr3(address_ddr3), //address line for accessing memory on the DDR3 memory
        .bank_address_ddr3(bank_address_ddr3), //Bank address for selecting specific memory within the DDR3
        .rbank_address_strobe_n(rbank_address_strobe_n), //Row address strobe 
        .cbanck_address_strobe_n(cbanck_address_strobe_n), //Column address strobe
        .reset_ddr3_n(reset_ddr3_n), //Reset signal for the DDR3 memory controller 
        .we_ddr3_n(we_ddr3_n), //Write enable (active low)
        .clk_ddr3_p(clk_ddr3_p), 
        .clk_ddr3_n(clk_ddr3_n), 
        .enable_clk(enable_clk), 
        .data_mask_ddr3(data_mask_ddr3), 
        .on_die_termination_ddr3(on_die_termination_ddr3), 
        .databus_ddr3(databus_ddr3), 
        .strobe_signal_p(strobe_signal_p), //positive strobe signal (for data alignment)
        .strobe_signal_n(strobe_signal_n) 
      );
      
      
      /*
        Memory controller 
      */
      
      
     wire lr_clk_rise; 
     reg pulse; 
     
     reg lr_clk_d1; 
     reg lr_clk_d2; 
     
   assign lr_clk_rise = lr_clk_d1 & ~lr_clk_d2;
   reg[3:0] lr_clk_count = 0; 
   always @(posedge clk ) begin 
       if (lr_clk_count == 8) begin 
           pulse <=1; 
           lr_clk_count  <=0; 
           end 
       else 
            pulse <=0;
            if (lr_clk_rise) begin
                lr_clk_count <= lr_clk_count + 1; 
            end 
      end
     
    
    
    memory_controller memory_controller_i (
        .clk(clk), 
        .rst(rst), 
        .pulse(pulse), 
        .playing(playing), 
        .recording(recording), 
        .read_data_valid(read_data_valid_rise), 
        .chip_enable_ram_n(chip_enable_memory), 
        .write_enable_ram_n(write_enable_memory), 
        .read_enable_ram_n(read_enable_memory), 
        .get_data(data_flag), 
        .data_ready(data_ready),
        .address_block_memory(address_block),
        .bank_memory(bank_memory)
    ); 
    
    assign input_memory = {16'h0000, sound_dataL[23:0], sound_dataR[23:0]};
      
      
    i2s_controller audio_inout(
        .CLK_I(clk),   
        .RST_I(rst),    
        .EN_TX_I(1),  
        .EN_RX_I(1), 
        .FS_I(4'b0101),   
        .MM_I(0),     
        .D_L_O(in_audioL),    
        .D_R_O(in_audioR),   
        .BCLK_O(serial_clk),   
        .LRCLK_O(channel_clk),  
        .SDATA_O(dac_serial_data),  
        .SDATA_I(adc_serial_data)   
    ); 

endmodule

module control(
    input clk,
    input rst, 
    input btn, 
    output reg [15:0] playing, 
    output reg [15:0] recording,
    output reg [15:0] active, 
    output reg [3:0] bank,
    input [21:0] current_address
    );
    
    reg state; 
    localparam DEFAULT = 4'd0;
    localparam PLAY = 4'd1; 
    localparam RECORD = 4'd2;
    localparam BUTTON = 4'd3; 
 
    /*
        Finite State machine 
    */
    
    always @(posedge clk) begin 
        if (rst) begin
            state <= DEFAULT; 
            active <= 4'd0; 
            playing <= 0; 
            recording <= 0; 
            bank <= 3'd0; 
        end else begin 
        case (state) 
        
            DEFAULT: begin 
                if (btn)begin 
                    state <= RECORD; 
                end 
            end 
            
            BUTTON: begin 
               if (btn == 0) 
                    state <= DEFAULT; 
            end
            
            PLAY: begin 
                playing[bank] <= 1;
                
                if (btn == 0) begin 
       //             state <= nstate; 
                end
            end 
            
            RECORD: begin 
                recording[bank] <= 1;
                playing[bank] <= 0; 
            end 
        endcase
       end 
    end 
endmodule

module audio(
    input wire clk, 
    input rst, 
    inout serial_clk, 
    inout serial_data
    );
    
    localparam RegAddr1 = 4'd0;
    localparam RegAddr2 = 4'd1;
    localparam Data1 = 4'd2; 
    localparam Data2 = 4'd3; 
    localparam Error = 4'd4; 
    localparam Done = 4'd5;
    localparam Idle = 4'd6;
    localparam Delay = 4'd7;
    localparam second = 4'd8;
    
    parameter init_vectors = 10; 
    parameter initialize_read = 1'b1;
    parameter initialize_write = 1'b0; 
    parameter delay = 30000; 
    
    reg [3:0] state = Idle; 
    reg [32:0] initial_word;
    reg init_Enable;
    reg init_Fb_We;
    reg [6:0] init_A = 0;
    
    always @(posedge clk) begin 
        case (init_A)
            0: initial_word <= {initialize_write,31'h40150100};
            1: initial_word <= {initialize_write,31'h40160000};
            2: initial_word <= {initialize_write,31'h40170000};
            3: initial_word <= {initialize_write,31'h40F80000};
            4: initial_word <= {initialize_write,31'h40191300};
            5: initial_word <= {initialize_write,31'h402A0300};
            6: initial_word <= {initialize_write,31'h40290300};
            7: initial_word <= {initialize_write,31'h40F20100};
            8: initial_word <= {initialize_write,31'h40F97F00};
            9: initial_word <= {initialize_write,31'h40FA0300};
            
            10: initial_word <= {initialize_write,31'h40200300};
            11: initial_word <= {initialize_write,31'h40220100};
            12: initial_word <= {initialize_write,31'h40210900};
            13: initial_word <= {initialize_write,31'h4025E600};
            14: initial_word <= {initialize_write,31'h4026E600};
            15: initial_word <= {initialize_write,31'h40270300};
            16: initial_word <= {initialize_write,31'h40100100};
            17: initial_word <= {initialize_write,31'h40280000};
            18: initial_word <= {initialize_write,31'h4023E600};
            19: initial_word <= {initialize_write,31'h4024E600};
            
            20: initial_word <= {initialize_write,31'h400A0100};
            21: initial_word <= {initialize_write,31'h400B0500};
            22: initial_word <= {initialize_write,31'h400C0100};
            23: initial_word <= {initialize_write,31'h400D0500};
            24: initial_word <= {initialize_write,31'h400E0300};
            25: initial_word <= {initialize_write,31'h400F0300};
            26: initial_word <= {initialize_write,31'h401C2100};
            27: initial_word <= {initialize_write,31'h401D0000};
            28: initial_word <= {initialize_write,31'h401E4100};
            29: initial_word <= {initialize_write,31'h401F0000};
            30: initial_word <= {initialize_write,31'h40F30100};
            31: initial_word <= {initialize_write,31'h40F40000};
            32: initial_word <= {initialize_write,31'h40000F00};
            33: initial_word <= {initialize_write,31'h4002007D};
            34: initial_word <= {initialize_write,31'h000C2101}; 
        endcase
    end
    
    reg [7:0] input_data; 
    reg [7:0] output_data; 
    wire [7:0] address; 
    wire done;
    wire error;
    reg [7:0] data; 
    reg enable_delay; 
    
    assign address [7:0] = {{7'b0111011}, {1'b0}}; 

    /* 
        TWI INSTANTIATION
    */
    
    TWI twi_controller (
        .MSG_I (message), 
        .STB_I (strobe), 
        .A_I (address), 
        .D_I (input_data),
        .D_O (output_data), 
        .DONE_O (done), 
        .ERR_O (error), 
        .CLK (clk), 
        .SRST (rst),
        .SDA (serial_data), 
        .SCL (serial_clock)
        );
endmodule


`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////////////


module uart_finite_state_machine(
        input wire clk
    );
    
    
     //*******************************************************
            // FSM
            localparam READ_CONTROL = 5'd4;
            localparam WRITE_CONTROL = 5'd5;
            localparam UART_SIGNAL_SELECT = 5'd6;
            localparam UART_DONE = 5'd7;
             
            
            
            
            //BITS_SELECT
            
            localparam UPPER = 1'd0;
            localparam LOWER = 1'd1;
            
            reg [1:0] signal_state = LOWER;
            
            reg [15:0] inc_count = 0;
            reg [4:0] uart_state = 5'd0;
            
            reg [7:0] uart_din;
            
            
             reg rst = 0;
            reg [7:0] din;
            reg [7:0] address; 
            reg w_en = 1;
            reg r_en = 0; 
            wire [7:0] dout;
            
            
            uart uart_i (
                .clk(clk),
                .rst(rst),
                .din(din),
                .address(address),
                .w_en(w_en),
                .r_en(r_en), 
                .dout(dout),
                .tx(tx));
                
              
            
            always @(posedge clk) begin 
                
                        case (uart_state) 
                        READ_CONTROL: begin 
                            w_en <= 0;
                            r_en <= 1;
                            address <= 1;
                            if (dout[1] == 1) begin
                                uart_state <= WRITE_CONTROL;
                            end
                        end
                        
                        WRITE_CONTROL: begin 
                            w_en <= 1;
                            r_en <= 0;
                            address <= 2;
                            din <= uart_din; //Number 
                            uart_state <= UART_SIGNAL_SELECT;  
                        end
                        
                        UART_SIGNAL_SELECT: begin
                        //Design a way to select a signal for the finite state state Machine of the UART. 
                        //UPPER BITS, LOWER BITS
                        //
                            case (signal_state)
                            
                            LOWER: begin
                                uart_din = inc_count[15:8];
                                uart_state = READ_CONTROL;
                                signal_state = UPPER; 
                            end
                            UPPER: begin
                              
                               uart_state = UART_DONE;
                            end
                        endcase
                        end 
                        
                        UART_DONE: begin 
                         w_en <= 0;
                         r_en <= 0;
                    
                        end  
            endcase 
          end
endmodule

(* CORE_GENERATION_INFO = "clock_gen,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=clock_gen,x_ipVersion=1.00.a,x_ipLanguage=VERILOG,numBlks=1,numReposBlks=1,numNonXlnxBlks=0,numHierBlks=0,maxHierDepth=0,numSysgenBlks=0,numHlsBlks=0,numHdlrefBlks=0,numPkgbdBlks=0,bdsource=USER,synth_mode=OOC_per_IP}" *) (* HW_HANDOFF = "clock_gen.hwdef" *) 
module clock_gen
   (clk_in1,
    clk_out1,
    clk_out2,
    clk_out3,
    clk_out4,
    locked,
    resetn);
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 CLK.CLK_IN1 CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME CLK.CLK_IN1, CLK_DOMAIN clock_gen_clk_in1, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, INSERT_VIP 0, PHASE 0.0" *) input clk_in1;
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 CLK.CLK_OUT1 CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME CLK.CLK_OUT1, CLK_DOMAIN clock_gen_clk_wiz_0_0_clk_out1, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, INSERT_VIP 0, PHASE 0.0" *) output clk_out1;
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 CLK.CLK_OUT2 CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME CLK.CLK_OUT2, CLK_DOMAIN clock_gen_clk_wiz_0_0_clk_out1, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, INSERT_VIP 0, PHASE 0.0" *) output clk_out2;
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 CLK.CLK_OUT3 CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME CLK.CLK_OUT3, CLK_DOMAIN clock_gen_clk_wiz_0_0_clk_out1, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, INSERT_VIP 0, PHASE 0.0" *) output clk_out3;
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 CLK.CLK_OUT4 CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME CLK.CLK_OUT4, CLK_DOMAIN clock_gen_clk_wiz_0_0_clk_out1, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, INSERT_VIP 0, PHASE 0.0" *) output clk_out4;
  output locked;
  (* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 RST.RESETN RST" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME RST.RESETN, INSERT_VIP 0, POLARITY ACTIVE_LOW" *) input resetn;

  wire clk_in1_1;
  wire clk_wiz_0_clk_out1;
  wire clk_wiz_0_clk_out2;
  wire clk_wiz_0_clk_out3;
  wire clk_wiz_0_clk_out4;
  wire clk_wiz_0_locked;

  assign clk_in1_1 = clk_in1;
  assign clk_out1 = clk_wiz_0_clk_out1;
  assign clk_out2 = clk_wiz_0_clk_out2;
  assign clk_out3 = clk_wiz_0_clk_out3;
  assign clk_out4 = clk_wiz_0_clk_out4;
  assign locked = clk_wiz_0_locked;
  clock_gen_clk_wiz_0_0 clk_wiz_0
       (.clk_in1(clk_in1_1),
        .clk_out1(clk_wiz_0_clk_out1),
        .clk_out2(clk_wiz_0_clk_out2),
        .clk_out3(clk_wiz_0_clk_out3),
        .clk_out4(clk_wiz_0_clk_out4),
        .locked(clk_wiz_0_locked));
endmodule


