% 2
%
% result
%
% ex2_2(1)
% input a: 12
% input b: 12
% input c: 12
% ans = 36
function y = ex2_2(x)

a = input('input a: ');
b = input('input b: ');
c = input('input c: ');

if x >= 0.5 && x < 1.5
    y = a * x * x + b * x + c;
elseif x >= 1.5 && x < 3.5
    y = a * power(sin(b), c) + x;
else x >= 3.5 && x < 5.5
    y = log(abs(b + c / x));
end
