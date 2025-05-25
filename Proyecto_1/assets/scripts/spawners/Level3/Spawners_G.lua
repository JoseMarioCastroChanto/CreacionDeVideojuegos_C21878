local timer = 0
local timer2 = 0
local mage = true
math.randomseed(123)
function update()
    timer = timer + get_delta_time()
    timer2 = timer2 + get_delta_time()
    prob = math.random(1, 100)
    if timer2 >= 22000 and mage then
        create_dynamic_entity(this, 1, 7, 5)
        timer2 = 0
        mage = false
    end
    if timer >= 5000 then
        if prob < 51 and prob > 25 then
            create_dynamic_entity(this, 1, 1, 10)
        elseif prob < 26 then
            create_dynamic_entity(this, 1, 2, 5)
        end
        timer = 0
    end
end