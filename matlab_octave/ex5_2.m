% 5
%
% result
% ex5_2
% ans = 1.8447e+19
function s = ex5_2
v = [];
for m = 0:63
    v = [v, power(2, m)];
end

s = sum(v);
