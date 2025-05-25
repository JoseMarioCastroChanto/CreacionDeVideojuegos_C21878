local timer = 0
math.randomseed(131415)
function update()
    timer = timer + get_delta_time()
    prob = math.random(1, 100)
    if timer >= 5000 then
        if prob < 41 and prob > 20 then
            create_dynamic_entity(this, -1, 1, 6)
        end
        if prob < 21 then 
            create_dynamic_entity(this, -1, 2, 4.2)
        end
        timer = 0
    end
end