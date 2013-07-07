% 一元二次方程求解

a = input('a = ? ');
b = input('b = ? ');
c = input('c = ? ');

d = [a, b, c];

x = roots(d);
disp(['x1 = ', num2str(x(1)), ', x2 = ', num2str(x(2))])
