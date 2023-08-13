`timescale 1ns/1ns
module MSDFF_Tb();
	reg d=1,c=1;
	wire q;
	MSDFF DL1(d,c,q);
	initial begin 
	#100 d=0;
	c=0;
	#100 c=1;
	#100 d=1;
	c=0;
	#100 d=0;
	c=1;
	#100 c=0;
	#100 d=1;
	c=1;
	#100 d=0;
	c=0;
	#100 c=1;
	#100 c=0;
	#100 ;
	end 
endmodule
