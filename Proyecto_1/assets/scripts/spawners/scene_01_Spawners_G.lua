local timer = 0
math.randomseed(123)
function update()
    timer = timer + get_delta_time()
    prob = math.random(1, 100)
    if timer >= 5000  then
        if  prob < 21  then 
        create_dynamic_entity(this, 1, 1, 10)
        end
        timer = 0
    end
end