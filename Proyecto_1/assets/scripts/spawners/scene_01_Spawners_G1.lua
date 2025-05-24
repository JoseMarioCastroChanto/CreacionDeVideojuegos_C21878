local timer = 0
local XD = false
math.randomseed(123)
function update()
    timer = timer + get_delta_time()
    prob = math.random(1, 100)
    if timer >= 5000 then
        if prob < 100 and not XD then
            create_dynamic_entity(this, -1, 3, 5)
            create_dynamic_entity(this, -1, 2, 7)
            XD = true
        end
        timer = 0
    end
end