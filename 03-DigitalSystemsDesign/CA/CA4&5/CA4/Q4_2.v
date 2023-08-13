module DLatch2(input D,Clk,output Q);
	wire dbar,s,r,clk_bar,Qbar;	
	not  I1(clk_bar,Clk);
	not  I2(dbar,D);
	nand  N1(s,dbar,clk_bar);
	nand  N2(r,D,clk_bar);
	nand  N3(Qbar,Q,s);
	nand  N4(Q,Qbar,r);
endmodule

