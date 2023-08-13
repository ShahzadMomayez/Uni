module Register(input [7:0]Pi,input clk,rst,output [7:0]Po);
	genvar i;
	generate
		for(i=0;i<8;i=i+1) begin: Dlatches
			DLatch DD(Pi[i],clk,rst,Po[i]);
		end
	endgenerate
endmodule

