player_velocity = 150
fixed_player_velocity = math.sqrt((player_velocity * player_velocity)/ 2)
original_width = 32
movementSprites = 4
staticSprites = 2
screen_width = 1500  


local animations = {
    default = {x = 0, y = 0, width = 32, height = 32},
    up = {x = 0, y = 160, width = 32, height = 32},
    down = {x = 0, y = 96, width = 32, height = 32},
    right = {x = 0, y = 128, width = 32, height = 32},
    left = {x = 0, y = 512, width = 32, height = 32} 
}


function update()
    local pos_x, pos_y = get_positionX(this), get_positionY(this)
    local vel_x, vel_y = 0, 0
    local is_pressed = false
    local current_scale = get_scale(this)

    -- Inputs y detección de dirección
    if is_action_activated("up") then
        vel_y = vel_y - 1
        is_pressed = true
        current_direction = "up"
    end
    
    if is_action_activated("down") then
        vel_y = vel_y + 1
        is_pressed = true
        current_direction = "down"
    end

    if is_action_activated("left") then 
        vel_x = vel_x - 1
        current_direction = "left"
        is_pressed = true
        player_velocity = 150
    end

    if is_action_activated("right") then 
        vel_x = vel_x + 1
        current_direction = "right"
        is_pressed = true
    end

    -- Corrección de velocidad
    if vel_y ~= 0 then
        vel_x, vel_y = vel_x * fixed_player_velocity, vel_y * fixed_player_velocity
    else
        vel_x, vel_y = vel_x * player_velocity, vel_y * player_velocity
    end

    -- Aplicar animación según dirección
    if is_pressed then
        local anim = animations[current_direction]
        set_srcRect(this, anim.width, anim.height, anim.x, anim.y)
        set_numFrames(this, movementSprites)
    else
        local anim = animations["default"]
        set_srcRect(this, anim.width, anim.height, anim.x, anim.y)
        set_numFrames(this, staticSprites)
    end


    set_velocity(this, vel_x, vel_y)


  
    pos_x, pos_y = get_positionX(this), get_positionY(this)
    local player_half_width = (original_width * current_scale) / 2


    if pos_x + player_half_width < 0 then
        set_position(this, screen_width + player_half_width, pos_y)


    elseif pos_x - player_half_width > screen_width then
        set_position(this, -player_half_width, pos_y)
    end

end