module lab10 (clk,reset,keypadCol,keypadRow,dot_row,dot_col);
	input clk;
	input reset;
	input [3:0]keypadCol;
	output [3:0]keypadRow;
	output [7:0]dot_row;
	output [7:0]dot_col;
	wire clk_div;
	wire [4:0]keypadBuf;
	Freq_div F1 (clk,clk_div);
	Checkkeypad C1 (clk_div,reset,keypadRow,keypadCol,keypadBuf);
	dot_display(clk_div, reset, keypadBuf,dot_row,dot_col);
endmodule

module Freq_div(clk,clk_div);
	input clk;
	output reg clk_div;
	reg [24:0]counter;
	always@(posedge clk) begin
		if (counter == 25'd25000) begin // 1000Hz  (50M / (desire frequency))/2
			clk_div = ~clk_div;
			counter = counter +1;
		end
		else if (counter == 25'd50000) begin  //(50M / (desire frequency))
			clk_div = ~clk_div;
			counter = 0;
		end
		else
			counter <= counter +1;
	end
endmodule

module Checkkeypad(clk_div,reset,keypadRow,keypadCol,keypadBuf);
	input clk_div;
	input reset;
	input [3:0]keypadCol;
	output reg[3:0]keypadRow;
	output reg [4:0] keypadBuf;
	always@(posedge clk_div or negedge reset) begin
		if (!reset)
		begin
			keypadRow <= 4'b1111;
			keypadBuf <= 5'b10000;
		end
		else begin
			case ({keypadRow,keypadCol})
				8'b1110_1110: keypadBuf <= 5'h7;
				8'b1110_1101: keypadBuf <= 5'h4;
				8'b1110_1011: keypadBuf <= 5'h1;
				8'b1110_0111: keypadBuf <= 5'h0;
				
				8'b1101_1110: keypadBuf <= 5'h8;
				8'b1101_1101: keypadBuf <= 5'h5;
				8'b1101_1011: keypadBuf <= 5'h2;
				8'b1101_0111: keypadBuf <= 5'ha;
				
				8'b1011_1110: keypadBuf <= 5'h9;
				8'b1011_1101: keypadBuf <= 5'h6;
				8'b1011_1011: keypadBuf <= 5'h3;
				8'b1011_0111: keypadBuf <= 5'hb;
				
				8'b0111_1110: keypadBuf <= 5'hc;
				8'b0111_1101: keypadBuf <= 5'hd;
				8'b0111_1011: keypadBuf <= 5'he;
				8'b0111_0111: keypadBuf <= 5'hf;
				
				8'b1111_1111: keypadBuf <= 5'b10000;
				8'b1111_1110: keypadRow <= 4'b1110;
				8'b1111_1101: keypadRow <= 4'b1110;
				8'b1111_1011: keypadRow <= 4'b1110;
				8'b1111_0111: keypadRow <= 4'b1110;
				default: keypadBuf <= keypadBuf;
				
			endcase
			case(keypadRow)
				4'b1110: keypadRow <= 4'b1101;
				4'b1101:	keypadRow <= 4'b1011;
				4'b1011:	keypadRow <= 4'b0111;
				4'b0111:	keypadRow <= 4'b1110;
				default: keypadRow <= 4'b1110;
			endcase
		end
	end
endmodule

module dot_display(clk_div, rst, state,dot_row,dot_col);

input clk_div, rst;
input[4:0]state;
output reg[7:0]dot_row, dot_col;

reg [2:0]row_count;


always@(posedge clk_div or negedge rst)
begin
		if(~rst)
		begin
			dot_row <= 8'b0;
			dot_col <= 8'b0;
			row_count <= 0;
		end
		else
		begin
			row_count <= row_count + 1;
			case(row_count)
				3'd0: dot_row <= 8'b01111111;
				3'd1: dot_row <= 8'b10111111;
				3'd2: dot_row <= 8'b11011111;
				3'd3: dot_row <= 8'b11101111;
				3'd4: dot_row <= 8'b11110111;
				3'd5: dot_row <= 8'b11111011;
				3'd6: dot_row <= 8'b11111101;
				3'd7: dot_row <= 8'b11111110;
				default:dot_row <= 8'b01111111;
			endcase
			case(state)
				5'd0:
					case(row_count)//0
						3'd0: dot_col <= 8'b00000000;
						3'd1: dot_col <= 8'b00000000;
						3'd2: dot_col <= 8'b00000000;
						3'd3: dot_col <= 8'b00000000;
						3'd4: dot_col <= 8'b00000000;
						3'd5: dot_col <= 8'b00000000;
						3'd6: dot_col <= 8'b11000000;
						3'd7: dot_col <= 8'b11000000;
						default:dot_col <= 8'b00000000;
					endcase
				5'd1:
				case(row_count)//1
						3'd0: dot_col <= 8'b00000000;
						3'd1: dot_col <= 8'b00000000;
						3'd2: dot_col <= 8'b00000000;
						3'd3: dot_col <= 8'b00000000;
						3'd4: dot_col <= 8'b00000000;
						3'd5: dot_col <= 8'b00000000;
						3'd6: dot_col <= 8'b00110000;
						3'd7: dot_col <= 8'b00110000;
						default:dot_col <= 8'b00000000;
					endcase
				5'd4:
				case(row_count)//4
						3'd0: dot_col <= 8'b00000000;
						3'd1: dot_col <= 8'b00000000;
						3'd2: dot_col <= 8'b00000000;
						3'd3: dot_col <= 8'b00000000;
						3'd4: dot_col <= 8'b00000000;
						3'd5: dot_col <= 8'b00000000;
						3'd6: dot_col <= 8'b00001100;
						3'd7: dot_col <= 8'b00001100;
						default:dot_col <= 8'b00000000;
					endcase
				5'd7:
				case(row_count)//7
						3'd0: dot_col <= 8'b00000000;
						3'd1: dot_col <= 8'b00000000;
						3'd2: dot_col <= 8'b00000000;
						3'd3: dot_col <= 8'b00000000;
						3'd4: dot_col <= 8'b00000000;
						3'd5: dot_col <= 8'b00000000;
						3'd6: dot_col <= 8'b00000011;
						3'd7: dot_col <= 8'b00000011;
						default:dot_col <= 8'b00000000;
					endcase
				5'd10:
				case(row_count)//A
						3'd0: dot_col <= 8'b00000000;
						3'd1: dot_col <= 8'b00000000;
						3'd2: dot_col <= 8'b00000000;
						3'd3: dot_col <= 8'b00000000;
						3'd4: dot_col <= 8'b11000000;
						3'd5: dot_col <= 8'b11000000;
						3'd6: dot_col <= 8'b00000000;
						3'd7: dot_col <= 8'b00000000;
						default:dot_col <= 8'b00000000;
					endcase
				5'd2:
				case(row_count)//2
						3'd0: dot_col <= 8'b00000000;
						3'd1: dot_col <= 8'b00000000;
						3'd2: dot_col <= 8'b00000000;
						3'd3: dot_col <= 8'b00000000;
						3'd4: dot_col <= 8'b00110000;
						3'd5: dot_col <= 8'b00110000;
						3'd6: dot_col <= 8'b00000000;
						3'd7: dot_col <= 8'b00000000;
						default:dot_col <= 8'b00000000;
					endcase
				5'd5:
				case(row_count)//5
						3'd0: dot_col <= 8'b00000000;
						3'd1: dot_col <= 8'b00000000;
						3'd2: dot_col <= 8'b00000000;
						3'd3: dot_col <= 8'b00000000;
						3'd4: dot_col <= 8'b00001100;
						3'd5: dot_col <= 8'b00001100;
						3'd6: dot_col <= 8'b00000000;
						3'd7: dot_col <= 8'b00000000;
						default:dot_col <= 8'b00000000;
					endcase
				5'd8:
				case(row_count)//8
						3'd0: dot_col <= 8'b00000000;
						3'd1: dot_col <= 8'b00000000;
						3'd2: dot_col <= 8'b00000000;
						3'd3: dot_col <= 8'b00000000;
						3'd4: dot_col <= 8'b00000011;
						3'd5: dot_col <= 8'b00000011;
						3'd6: dot_col <= 8'b00000000;
						3'd7: dot_col <= 8'b00000000;
						default:dot_col <= 8'b00000000;
					endcase
				5'd11:
				case(row_count)//B
						3'd0: dot_col <= 8'b00000000;
						3'd1: dot_col <= 8'b00000000;
						3'd2: dot_col <= 8'b11000000;
						3'd3: dot_col <= 8'b11000000;
						3'd4: dot_col <= 8'b00000000;
						3'd5: dot_col <= 8'b00000000;
						3'd6: dot_col <= 8'b00000000;
						3'd7: dot_col <= 8'b00000000;
						default:dot_col <= 8'b00000000;
					endcase
				5'd3:
				case(row_count)//3
						3'd0: dot_col <= 8'b00000000;
						3'd1: dot_col <= 8'b00000000;
						3'd2: dot_col <= 8'b00110000;
						3'd3: dot_col <= 8'b00110000;
						3'd4: dot_col <= 8'b00000000;
						3'd5: dot_col <= 8'b00000000;
						3'd6: dot_col <= 8'b00000000;
						3'd7: dot_col <= 8'b00000000;
						default:dot_col <= 8'b00000000;
					endcase
				5'd6:
				case(row_count)//6
						3'd0: dot_col <= 8'b00000000;
						3'd1: dot_col <= 8'b00000000;
						3'd2: dot_col <= 8'b00001100;
						3'd3: dot_col <= 8'b00001100;
						3'd4: dot_col <= 8'b00000000;
						3'd5: dot_col <= 8'b00000000;
						3'd6: dot_col <= 8'b00000000;
						3'd7: dot_col <= 8'b00000000;
						default:dot_col <= 8'b00000000;
					endcase
				5'd9:
				case(row_count)//9
						3'd0: dot_col <= 8'b00000000;
						3'd1: dot_col <= 8'b00000000;
						3'd2: dot_col <= 8'b00000011;
						3'd3: dot_col <= 8'b00000011;
						3'd4: dot_col <= 8'b00000000;
						3'd5: dot_col <= 8'b00000000;
						3'd6: dot_col <= 8'b00000000;
						3'd7: dot_col <= 8'b00000000;
						default:dot_col <= 8'b00000000;
					endcase
				5'd15:
				case(row_count)//F
						3'd0: dot_col <= 8'b11000000;
						3'd1: dot_col <= 8'b11000000;
						3'd2: dot_col <= 8'b00000000;
						3'd3: dot_col <= 8'b00000000;
						3'd4: dot_col <= 8'b00000000;
						3'd5: dot_col <= 8'b00000000;
						3'd6: dot_col <= 8'b00000000;
						3'd7: dot_col <= 8'b00000000;
						default:dot_col <= 8'b00000000;
					endcase
				5'd14:
				case(row_count)//E
						3'd0: dot_col <= 8'b00110000;
						3'd1: dot_col <= 8'b00110000;
						3'd2: dot_col <= 8'b00000000;
						3'd3: dot_col <= 8'b00000000;
						3'd4: dot_col <= 8'b00000000;
						3'd5: dot_col <= 8'b00000000;
						3'd6: dot_col <= 8'b00000000;
						3'd7: dot_col <= 8'b00000000;
						default:dot_col <= 8'b00000000;
					endcase
				5'd13:
				case(row_count)//D
						3'd0: dot_col <= 8'b00001100;
						3'd1: dot_col <= 8'b00001100;
						3'd2: dot_col <= 8'b00000000;
						3'd3: dot_col <= 8'b00000000;
						3'd4: dot_col <= 8'b00000000;
						3'd5: dot_col <= 8'b00000000;
						3'd6: dot_col <= 8'b00000000;
						3'd7: dot_col <= 8'b00000000;
						default:dot_col <= 8'b00000000;
					endcase
				5'd12:
				case(row_count)//C
						3'd0: dot_col <= 8'b00000011;
						3'd1: dot_col <= 8'b00000011;
						3'd2: dot_col <= 8'b00000000;
						3'd3: dot_col <= 8'b00000000;
						3'd4: dot_col <= 8'b00000000;
						3'd5: dot_col <= 8'b00000000;
						3'd6: dot_col <= 8'b00000000;
						3'd7: dot_col <= 8'b00000000;
						default:dot_col <= 8'b00000000;
					endcase
				//all dark
				default:
				case(row_count)
						3'd0: dot_col <= 8'b00000000;
						3'd1: dot_col <= 8'b00000000;
						3'd2: dot_col <= 8'b00000000;
						3'd3: dot_col <= 8'b00000000;
						3'd4: dot_col <= 8'b00000000;
						3'd5: dot_col <= 8'b00000000;
						3'd6: dot_col <= 8'b00000000;
						3'd7: dot_col <= 8'b00000000;
						default:dot_col <= 8'b00000000;
					endcase
			endcase
		end
end
endmodule