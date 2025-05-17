local timer = 0

function update()
    timer = timer + get_delta_time()

    if timer >= 5000 then
        create_dynamic_entity(this, 1, 1, 10)
        timer = 0
    end
end