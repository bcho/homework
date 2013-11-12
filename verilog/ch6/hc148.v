module hc148 (in, eo, out, ei, gs);
    input[7:0] in;
    input ei;
    output eo;
    output[2:0] out;
    output gs;
    reg[2:0] out;
    reg eo;
    reg gs;
    integer i;

    always @(in or ei)
    begin:local
        if (ei)
        begin
            out = 7;
            eo = 1;
            gs = 1;
        end
        else if (in == 8'b11111111)
        begin
            out = 7;
            eo = 0;
            gs = 1;
        end
        else
            for (i = 0;i < 9;i = i + 1)
            begin
                if (~in[i])
                begin
                    out = ~i;
                    eo = 1;
                    gs = 0;
                end
            end
    end
endmodule

`timescale 1ns/10ps

module test();
    reg[7:0] in;
    reg ei;
    // TODO why wire?
    wire eo, gs;
    wire[2:0] out;

    initial
    begin
        in = 'b1;
        ei = 0;
        repeat(9) #20 in = in << 1;

        ei = 1;
        in = 'b1;
        repeat(9) #20 in = in << 1;

        ei = 0;
        in = 8'b11111111;
        repeat(9) #20 in = in << 1;
    end

    hc148 g(in, eo, out, ei, gs);

    initial
        $monitor("time = %t, in = %b, out = %b, eo = %b, ei = %b, gs = %b",
                 $time, in, out, eo, ei, gs);
endmodule
