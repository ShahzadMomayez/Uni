module SRAS(input sin,clk,rs,output reg [7:0]Paro,Qb,output So);
	always @(posedge clk,posedge rs)begin
		if (rs) begin
			Paro<=8'b00000000;
			Qb<=8'b11111111;
		end
		else begin
			Paro<={sin,Paro[7:1]};
			Qb<={~sin,~Paro[7:1]};
		end
	end
	assign So=Paro[0];
endmodule