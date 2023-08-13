module ShiftRegTB();
	reg si=1,clk=0,r=0;
	wire so;
	wire [7:0] parout;
	ShiftRG	U1(si,clk,r,so,parout);
	initial begin
	#100
	si=0;
	#100
	clk=1;
	#100
	si=1;
	clk=0;
	#100 si=0;
	#100 si=1;
	#100;
	end 
endmodule
