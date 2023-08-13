module LFSR(input clk , rst, output [7:0] paro);
	SRAS lfsr(~(~(~(paro[0]^paro[2])^paro[3])^paro[4]),clk,rst,paro,paro[0]);
endmodule
