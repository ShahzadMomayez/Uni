`timescale 1ns/1ns
module SRTb();
	reg ss=1,rr=1,c=1;
	wire q,qbar;
	SRLatch SR1(ss,rr,c,q,qbar);
	initial begin 
	#100 ss=0;
	#100 c=0;
	#100 ss=1;
	#100 rr=0;
	#100 c=1;
	#100 rr=1;
	#100 ss=0;
	rr=0;
	c=0;
	#100 ss=1;
	c=1;
	#100 ss=0;
	#100 rr=1;
	end 
endmodule
