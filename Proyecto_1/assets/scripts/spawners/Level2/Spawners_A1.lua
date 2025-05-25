local timer = 0
math.randomseed(192021)

function update()
    timer = timer + get_delta_time()
    prob = math.random(1, 100)
    if timer >= 10000 then
        if prob < 21 and prob > 10 then
            create_dynamic_entity(this, -1, 1, 4)
        end
        if prob < 11 then 
            create_dynamic_entity(this, -1, 2, 4.8)
        end
        timer = 0
    end
end