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
// Description: I am creating a light weight IP that is goihng to sample sound, process it, store it in memory
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
