module DLatch(input D,Clk,rs,output Q);
	wire dbar,s,r,clk_bar,q,Qbar;	
	not  I1(clk_bar,Clk);
	not  I2(dbar,D);
	nand  N1(s,dbar,clk_bar);
	nand  N2(r,D,clk_bar);
	nand  N3(Qbar,q,s);
	nand  N4(q,Qbar,r);
	assign Q=(clk_bar&rs)?1'b0:q;
endmodule
