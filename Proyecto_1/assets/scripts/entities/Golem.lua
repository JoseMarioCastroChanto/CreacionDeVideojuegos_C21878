local animations = {
    left = {x = 0, y = 0, width = 80, height = 64},
    right = {x = 0, y = 64, width = 80, height = 64},
    leftAttack = {x = 0, y = 128, width = 80, height = 64}, 
    rightAttack = {x = 0, y = 192, width = 80, height = 64}, 
}

local elapsed = 0
local impulse_duration = 500  
local impulse_applied = false
local current_direction = "right"  
local last_direction = "right"

local tolerance_x = 1   
local tolerance_y = 1  

function update()
    local dt = get_delta_time() * 1000
    elapsed = elapsed + dt

    local objective_posX = search_objectiveX(this, false)
    local objective_posY = search_objectiveY(this, false)
    local objective_scale = search_objectiveScale(this, false)
    local objective_depth = search_objectiveDepth(this, false)

    local scale = get_scale(this)
    local depth = get_depth(this)
    local posX = get_positionX(this)
    local posY = get_positionY(this)
    local vel_x = get_velocity(this)

    local close_enough_x = math.abs(objective_posX - posX) <= tolerance_x
  

    if close_enough_x  then
        print("llego")
        set_velocity(this, 0, 0)
        impulse_applied = false
        elapsed = 0
        if last_direction == "right" then
            current_direction = "rightAttack"
        else
            current_direction = "leftAttack"
        end
    else
        -- Todavía se mueve, actualizar dirección según velocidad X
        if vel_x > 0 then
            current_direction = "right"
            last_direction = "right"
        elseif vel_x < 0 then
            current_direction = "left"
            last_direction = "left"
        end

        local obj_scaleT = (objective_scale * 10) / objective_depth
        local scaleT = (scale * 10) / depth

        if not impulse_applied then
            local dy = (obj_scaleT - scaleT) * 20
            if math.abs(dy) > 1 or dy < 1 then
                local dirY = dy / math.abs(dy)
                set_velocity(this, vel_x, dirY * 2.5)
                impulse_applied = true
                elapsed = 0
            end
        elseif elapsed >= impulse_duration then
            set_velocity(this, vel_x, 0)
            impulse_applied = false
        end
    end

    local anim = animations[current_direction]
    set_srcRect(this, anim.width, anim.height, anim.x, anim.y)
end