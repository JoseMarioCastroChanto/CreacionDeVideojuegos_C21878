local timer = 0
math.randomseed(192021)

function update()
    timer = timer + get_delta_time()
    prob = math.random(1, 100)
    if timer >= 10000 then
        if prob < 21 and prob > 5 then
            create_dynamic_entity(this, 1, 1, 4)
        end
        if prob < 6 then 
            create_dynamic_entity(this, 1, 3, 2.2)
        end
        timer = 0
    end
end