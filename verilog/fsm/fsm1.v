module fsm(clk, rst, ina, out);
    input clk, rst, ina;
    output out;
    reg out;

    parameter s0 = 2'b00,
              s1 = 2'b01,
              s2 = 2'b10,
              s3 = 2'b11;

    reg[0:1] state;

    always @(posedge clk or negedge rst)
        if (!rst)
        begin
            state <= s0;
            out = 0;
        end
        else
        begin
            case (state)
                s0:
                begin
                    state <= (ina) ? s1 : s0;
                    out = 0;
                end
                s1:
                begin
                    state <= (ina) ? s2 : s0;
                    out = 0;
                end
                s2:
                begin
                    state <= (ina) ? s3 : s0;
                    out = 0;
                end
                s3:
                begin
                    state <= (ina) ? s3 : s0;
                    out = 1;
                end
            endcase
        end
endmodule

`timescale 1ns/1ns

module test;
    reg ina, rst, clk;
    parameter clock_period = 20;

    always #(clock_period / 2) clk = ~clk;

    initial
    begin
        clk = 0;
        rst = 1;
        #25 rst = 0;
        #75 rst = 1;
        #200 $finish;
    end

    initial
    begin
        ina = 0;
        #5;
        repeat(10)
            #30 ina = $random;
    end
endmodule
