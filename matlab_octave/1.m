x1 = input('x1=? ');

x = pi / 3.0 - acos(15.0 * cos(x1) / 16);

while abs(x - x1) >= 10e-8
    x1 = x;
    x = pi / 3.0 - acos(15.0 * cos(x1) / 16);

    if x > pi / 3.0
        disp('error');
    end
end

y = x1 * 180 / pi
