`timescale 1ns/1ns
module ShiftReg2TB();
	reg si=1,clk=1,rst=0;
	wire so;
	wire[7:0] parout;
	shifter8_MSDFF U2(si , rst , clk ,parout,so);
	initial begin
	#10
	clk=0;
	#10
	si=0;
	#100
	clk=1;
	#10
	si=1;
	#10
	clk=0;
	#10;
	clk=1;
	#10
	si=1;
	#10
	clk=0;
	#10;
	clk=1;
	#10
	si=1;
	#10
	clk=0;
	#10;
	end 
endmodule
