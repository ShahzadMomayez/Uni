module MSDFF(input D,clk,output Q);
	wire clk_bar,q1;
	not I1(clk_bar,clk);
	DLatch2 D1(D,clk,q1);
	DLatch2 D2(q1,clk_bar,Q);
endmodule

