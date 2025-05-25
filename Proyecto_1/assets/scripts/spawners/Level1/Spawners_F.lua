local timer = 0
math.randomseed(456)
function update()
    timer = timer + get_delta_time()
    prob = math.random(1, 100)
    if timer >= 10000 then
        if prob < 31 and prob > 15 then
            create_dynamic_entity(this, 1, 1, 9)
        end
        if prob < 16 then 
            create_dynamic_entity(this, 1, 2, 6.3)
        end
        timer = 0
    end
end