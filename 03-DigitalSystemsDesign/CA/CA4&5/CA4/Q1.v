module SRLatch(input S,R,Clk,output Q,Qbar);
	wire s,r,clk_bar;	
	not  I1(clk_bar,Clk);
	nand  N1(s,S,clk_bar);
	nand  N2(r,R,clk_bar);
	nand  N3(Qbar,Q,s);
	nand  N4(Q,Qbar,r);
endmodule
