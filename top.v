`timescale 1ns / 1ps

/*************************************/

/* Last Modified: April 29 2024 

/****************************************/


module top (
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
