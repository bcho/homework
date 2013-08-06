-- **Next Prime Number**
-- Have the program find prime numbers
-- until the user chooses to stop asking for the next one.

require 'utils'


known_primes = {}


first_cal = function(upper)
    local i
    local sequences = {}

    for i = 2, upper + 1 do
        sequences[#sequences + 1] = true
    end

    for i = 2, upper + 1 do
        if sequences[i] then
            local j = 2
            while true do
                if i * j > upper then
                    break
                end -- end if
                sequences[i * j] = false
                j = j + 1
            end -- end while
        end -- end if
    end

    for i = 2, upper + 1 do
        if sequences[i] then
            known_primes[#known_primes + 1] = i
        end -- end if
    end -- endfor

end


is_prime = function(num)
    local i
    local _ = true

    for k, v in pairs(known_primes) do
        if v > math.sqrt(num) then
            break
        end -- end if
        if num % v == 0 then
            _ = false
            break
        end -- end if
    end -- end for

    return _
end

get_next_prime = function(lower)
    local i = lower + 1

    while true do
        if is_prime(i) then
            known_primes[#known_primes + 1] = i
            return i
        end -- end if
        i = i + 1
    end -- end while
end


loop = function()
    io.write('tell me where you want to start with: ')
    local start = tonumber(io.read())

    if not start then
        print('you should input a number')
    end -- end if

    first_cal(start)

    while true do
        start = get_next_prime(start)
        print(start)

        io.write('would you like to continue? y/n ')
        local choice = io.read()
        if choice:lower() == 'n' then
            return
        end -- end if
    end
end

loop()
