local timer = 0
math.randomseed(192021)

function update()
    timer = timer + get_delta_time()
    prob = math.random(1, 100)
    if timer >= 5000 then
        if prob < 51 and prob > 25 then
            create_dynamic_entity(this, 1, 1, 4)
        elseif prob < 26 then
            create_dynamic_entity(this, 1, 2, 2.8)
        end
        timer = 0
    end
end