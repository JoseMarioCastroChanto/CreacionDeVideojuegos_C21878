local cooldown = 0
local bigBomb = 0
local l_pressed_last_frame = false

function update()
    cooldown = cooldown + get_delta_time()
    if cooldown >= 10000 then
        bigBomb = bigBomb + 1
        cooldown = 0
        set_text(this, bigBomb)
    end

    local l_pressed = is_action_activated("l")

    if l_pressed and not l_pressed_last_frame and bigBomb > 0 then
        bigBomb = bigBomb - 1
        print(bigBomb)
        set_text(this, bigBomb)
    end

    l_pressed_last_frame = l_pressed
end
