local timer = 0
math.randomseed(789)
function update()
    timer = timer + get_delta_time()
    prob = math.random(1, 100)
    if timer >= 8000 and prob < 41 then
        create_dynamic_entity(this, -1, 1, 8)
        timer = 0
    end
end