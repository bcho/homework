module var1;

reg[4:-1] pa, pb;
initial
begin
    pa = -2;
    pb = 5;
    $display("%d, %d", pa, pb);
end
endmodule
