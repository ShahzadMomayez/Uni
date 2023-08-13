`timescale 1ns/1ns
module Q3_TB();
    logic c = 1'b0;
    logic r = 1'b0;
    logic j = 1'b0;
    wire w1, w2, diff;
    MealySVerilogPP uut1(.clk(c), .rst(r), .j(j), .w(w2));
    MooreSVPP uut2(.clk(c), .rst(r), .j(j), .w(w1));
    always #50 c = ~c;
    initial begin
        #100 j = 1'b0;
        #100 j = 1'b1;
        #100 j = 1'b0;
        #100 j = 1'b1;
        #100 j = 1'b1;
        #100 j = 1'b0;
        #100 j = 1'b1;
        #100 j = 1'b1;
        #100 $stop;
    end
    assign #(1) diff = w1 ^ w2;
endmodule
