module fsm(clk, rst, ina, dataout);
    input clk, rst, ina;
    output dataout;
    reg dataout;

    parameter s0 = 2'b00,
              s1 = 2'b01,
              s2 = 2'b10,
              s3 = 2'b11;

    reg[0:1] current_state, next_state;

    always @(posedge clk or negedge rst)
        if (!rst)
            current_state <= s0;
        else
            current_state <= next_state;

    always @(current_state or ina)
    begin
        next_state <= s0;

        case (current_state)
            s0:
                if (ina == 1)
                    next_state <= s1;
            s1:
                if (ina == 1)
                    next_state <= s2;
            s2:
                if (ina == 1)
                    next_state <= s3;
            s3:
                if (ina == 1)
                    next_state <= s3;
        endcase
    end

    assign dataout = (current_state == s3);
endmodule
