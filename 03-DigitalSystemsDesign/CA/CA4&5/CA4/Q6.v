module ShiftRG(input sin,clk,rst,output sout,output[7:0] Po);
	DLatch D8(sin,clk,rst,Po[7]);
	DLatch D7(Po[7],clk,rst,Po[6]);
	DLatch D6(Po[6],clk,rst,Po[5]);		
	DLatch D5(Po[5],clk,rst,Po[4]);
	DLatch D4(Po[4],clk,rst,Po[3]);
	DLatch D3(Po[3],clk,rst,Po[2]);	
	DLatch D2(Po[2],clk,rst,Po[1]);
	DLatch D1(Po[1],clk,rst,Po[0]);
	assign sout=Po[0];
endmodule

