% 5
%
% result
%
% ex5_1
% ans = 1.8447e+19
function s = ex5_1
s = 0;
for m = 0:63
    s = s + power(2, m);
end
