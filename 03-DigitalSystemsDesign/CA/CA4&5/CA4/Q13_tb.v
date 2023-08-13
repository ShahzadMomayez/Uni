`timescale 1ns/1ns
module lfsr_tb();
	reg clk =0 , rst = 0;
	wire [7:0] pp;
	LFSR sr(clk , rrst , pp);
	initial begin 
		#10 rst = 1 ; clk = 1;
		#30 clk = 0;
		#10 rst = 0;
		repeat(300) #50 clk = ~clk;
		#50 $stop;
	end
endmodule
	
