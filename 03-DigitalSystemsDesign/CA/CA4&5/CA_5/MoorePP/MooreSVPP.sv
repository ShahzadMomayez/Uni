`timescale 1ns/1ns
module MooreSVPP(input clk, rst, j, output w);
    logic[2:0] ns, ps;
    parameter [2:0] A=3'd0, B=3'd1, C=3'd2, D=3'd3, E=3'd4, F=3'd5;
    always@(ps, j) begin
        ns = A;
            case(ps)
                A: ns= j ? B : A;
                B: ns= j ? B : C;
                C: ns= j ? D : A;
                D: ns= j ? E : C;
                E: ns= j ? B : F;
                F: ns= j ? D : A;
                default: ns= A;
            endcase
    end
    assign w= (ps == F) ? 1'b1 : 1'b0;
    always@(posedge clk, posedge rst) begin
        if (rst)
            ps <= A;
        else
            ps <= ns;
    end
endmodule
