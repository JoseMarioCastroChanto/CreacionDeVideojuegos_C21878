local timer = 0
math.randomseed(101112)
function update()
    timer = timer + get_delta_time()
    prob = math.random(1, 100)
    if timer >= 5000 then
        if prob < 100 then
            create_dynamic_entity(this, -1, 3, 8.4)
        end
        timer = 0
    end
end
-- 8.4
-- 4.9
-- 7