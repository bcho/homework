-- **Prime Factorization**
-- Have the user enter a number and find all Prime Factors (if there are any)
-- and display them.


factor = function(num)
    local i = 2;
    local factors = {};

    if not num or num < 1 then
        print('your input must be postive!')
    end

    if num and num == 1 then
        factors[1] = 1
        return factors
    end

    while num and num > 1 do
        while num % i == 0 do
            factors[#factors + 1] = i
            num = num / i
        end
        i = i + 1
    end

    return factors
end


print_table = function(t)
    for k, v in pairs(t) do
        io.write(v .. ' ')
    end
    io.write('\n')
end


print_table(factor(tonumber(io.read())))
