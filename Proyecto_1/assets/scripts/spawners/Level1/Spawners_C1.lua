local timer = 0
math.randomseed(131415)
function update()
    timer = timer + get_delta_time()
    prob = math.random(1, 100)
    if timer >= 5000 and prob < 51 then
        create_dynamic_entity(this, -1, 1, 6)
        timer = 0
    end
end