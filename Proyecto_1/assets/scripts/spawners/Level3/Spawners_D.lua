local timer = 0
math.randomseed(101112)
function update()
    timer = timer + get_delta_time()
    timer2 = timer2 + get_delta_time()
    prob = math.random(1, 100)
    if timer2 >= 12000 then
        create_dynamic_entity(this, 1, 7, 3.5)
        timer2 = 0
    end
    if timer >= 6500 then
        if prob < 51 and prob > 25 then
            create_dynamic_entity(this, 1, 1, 7)
        elseif prob < 26 then
            create_dynamic_entity(this, 1, 2, 4.9)
        end
        timer = 0
    end
end