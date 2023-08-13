`timescale 1ns/1ns
module Q1_TB();
    logic c = 1'b0;
    logic r = 1'b0;
    logic j = 1'd0;
    wire w;
    moore10110 mn(.clk(c), .rst(r), .j(j), .w(w));
    always #50 c = ~c;
    initial begin
        #100 j = 1'd0;
        #100 j = 1'd1;
        #100 j = 1'd0;
        #100 j = 1'd1;
        #100 j = 1'd1;
        #100 j = 1'd0;
        #100 j = 1'd1;
        #100 j = 1'd1;
        #100 j = 1'd0;
        #200 $stop;
    end
endmodule
