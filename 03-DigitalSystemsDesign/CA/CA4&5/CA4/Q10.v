module shifter8_MSDFF(input sin , rst , clk , output[7:0] pout , output sout);
	wire [8:0] wsh;
	genvar i;
	generate 
		for (i=8 ; i>0 ; i=i-1) begin
			MSDFF m(wsh[i] , clk , wsh[i-1]);
		end
	endgenerate
	assign wsh[8] = sin;
	assign pout = rst?8'b0:wsh[7:0];
	assign sout = rst?1'b0:wsh[0];
endmodule
