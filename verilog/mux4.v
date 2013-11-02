module mux4(y, d0, d1, d2, d3, s1, s0);
    output y;
    input d0, d1, d2, d3;
    input s1, s0;

    assign y = (~s1 & ~s0 & d0) |
               (~s1 & s0 & d1) |
               (s1 & ~s0 & d2) |
               (s1 & s0 & d3);
endmodule
