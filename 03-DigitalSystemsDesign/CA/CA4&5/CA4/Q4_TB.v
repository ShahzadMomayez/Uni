`timescale 1ns/1ns
module DLTb();
	reg d=1,c=1,r=0;
	wire q;
	DLatch DL1(d,c,r,q);
	initial begin 
	#100 d=0;
	#100 c=0;
	#100 d=1;
	#100 d=0;
	#100 c=1;
	#100 d=1;
	#100 c=0;
	#100 c=1;
	#100 r=1;
	#100 c=0;
	#100 ;
	end 
endmodule
