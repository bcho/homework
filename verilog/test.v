module mux (out, a, b, sel);
    input a, b, sel;
    output out;

    assign out = (sel) ? (b) : (a);
endmodule

module test;
    reg pa, pb, psel;
    wire pout;
    mux tmux(pout, pa, pb, psel);
initial
fork
    pa = 0; pb = 0; psel = 0;
    #5 pa = 1;
    #5 pb = 1;
    #5 pa = 0;
    #5 psel = 1;
    #5 pa = 1;
    #5 pb = 0;
    #5 pa = 0;
join
initial
begin
    $monitor("time=%t, a = %b, b = %b, sel = %b, out = %b",
               $time, pa, pb, psel, pout);
end
endmodule
