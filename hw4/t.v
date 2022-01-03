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

module Checkkeypad(clk_div,reset,keypadBuf);
    input clk_div;
	input reset;
	output reg [4:0] keypadBuf;
    reg[31:0]
endmodule