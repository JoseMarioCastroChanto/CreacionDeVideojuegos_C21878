timer = 0
function update()
    timer = timer + get_delta_time() 
    if timer >= 1700 then
        destroy_all_enemies()
        kill(this)
    end
end