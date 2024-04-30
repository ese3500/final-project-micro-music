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
