module var2;

wire pa;
wire[0:7] pb;
integer pc[0:7], pd[4:0];
reg[1:2] px;
wire[0:7] pe[0:3];
initial
begin
    pd[0] = 15;
    px = 3;
    $display("%d, %d", pd[0], px);
end
endmodule
