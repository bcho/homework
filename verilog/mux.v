module mux (out, a, b, sel);
    input a, b, sel;
    output out;
    reg out;

always @(a, b, sel)
    out = (sel) ? (b) : (a);
endmodule
