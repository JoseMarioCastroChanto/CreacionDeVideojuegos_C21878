timer = 0
function update()
    timer = timer + get_delta_time() 
    if timer >= 1800 then
        kill(this)
    end
end