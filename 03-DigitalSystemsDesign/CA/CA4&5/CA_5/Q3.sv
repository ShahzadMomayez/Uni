`timescale 1ns/1ns
module Q3_TB();
    logic c = 1'b0;
    logic r = 1'b0;
    logic j;
    wire w1, w2, diff;
    mealy10110 uut1(.clk(c), .rst(r), .j(j), .w(w2));
    moore10110 uut2(.clk(c), .rst(r), .j(j), .w(w1));
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
    assign diff = w1 ^ w2;
endmodule
