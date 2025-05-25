local timer = 0
math.randomseed(101112)
function update()
    timer = timer + get_delta_time()
    prob = math.random(1, 100)
    if timer >= 5000 then
        if prob < 100 then 
            create_dynamic_entity(this, 1, 2, 4.9)
        end
        timer = 0
    end
end