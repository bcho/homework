module encoder83(in, eo, out);
    input[7:0] in;
    output eo;
    output[2:0] out;
    reg eo;
    reg[2:0] out;
    integer i;

    always @(in) // subscribe to input
    begin
        out = 0;
        eo = 1; // encode error
        for (i = 0;i < 8;i = i + 1)
        begin
            if (in[i])
            begin
                out = i;
                eo = 0;
            end
        end
    end
endmodule

`timescale 1ns/10ps

module test();
    reg[7:0] in;
    // TODO why wire? every gate's out's type needs to be wire?
    wire[2:0] out;
    wire EO;

    initial
    begin
        in = 'b1;
        repeat(9) #20 in = in << 1;
    end

    encoder83 test(in, eo, out);

    initial
        $monitor("time = %t, in = %b, out = %b, eo = %b", $time, in, out, eo);
endmodule
