module gates(a, b, y1, y2, y3, y4, y5);
    input a, b;
    output y1, y2, y3, y4, y5;

    assign y1 = a & b;
    assign y2 = a | b;
    assign y3 = a ^ b;
    assign y4 = ~y1;
    assign y5 = ~y2;
endmodule

`timescale 1ns/1ns

module test();
    reg a, b;
    // TODO why use wire?
    wire y1, y2, y3, y4, y5;

    gates test_gates(a, b, y1, y2, y3, y4, y5);

    initial
    begin
        a = 0; b = 0;
        #10 b = 1;
        #10 a = 1;
        #10 b = 0;
        #10;
    end

    initial
        $monitor("time = %t, a = %b, b = %b, y1 = %b, y2 = %b, y3 = %b y4 = %b, y5 = %b",
                 $time, a, b, y1, y2, y3, y4, y5);
endmodule
