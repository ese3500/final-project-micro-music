`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////////////


module debounce_module (
    input clk,
    input rst, 
    input button, 
    output reg out
    );
    
    reg [13:0] counter = 0; 
    
    always @(posedge clk) begin 
        if (rst) begin 
            counter <= 0; 
        end else begin 
            if (counter == 4000) begin 
                counter <= 0; 
                out <= button; 
            end else begin 
                 counter <= counter + 1;
            end 
        end 
       end
endmodule
