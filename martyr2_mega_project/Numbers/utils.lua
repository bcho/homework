-- utils.lua
-- some usefule function

print_table = function(t)
    for k, v in pairs(t) do
        io.write(v .. ' ')
    end -- end for
    io.write('\n')
end
