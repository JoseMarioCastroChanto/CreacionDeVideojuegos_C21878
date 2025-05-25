local timer = 0
local timer2 = 0
local mage = true

math.randomseed(192021)

function update()
    timer = timer + get_delta_time()
    timer2 = timer2 + get_delta_time()
    prob = math.random(1, 100)
    if timer2 >= 85000 and mage then
        create_dynamic_entity(this, 1, 8, 2)  
        timer2 = 0
        mage = false
    end
    if timer >= 5000 then
        if prob < 51 and prob > 25 then
            create_dynamic_entity(this, 1, 1, 4)
        elseif prob < 26 then
            create_dynamic_entity(this, 1, 2, 2.8)
        end
        timer = 0
    end
end