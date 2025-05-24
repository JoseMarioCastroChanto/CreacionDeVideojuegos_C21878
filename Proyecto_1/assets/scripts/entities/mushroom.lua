local animations = {
    right = {x = 0, y = 0, width = 80, height = 64},
    left  = {x = 0, y = 64, width = 80, height = 64},
}

local elapsed = 0
local impulse_duration = 1000  
local impulse_applied = false
local current_direction = "right"  


local last_objective_posX = nil
local last_objective_scaleT = nil

function update()
    local dt = get_delta_time() * 1000
    elapsed = elapsed + dt


    local objective_posX = search_objectiveX(this, true)
    local objective_posY = search_objectiveY(this, true)
    local objective_scale = search_objectiveScale(this, true)
    local objective_depth = search_objectiveDepth(this, true)

 
    local scale = get_scale(this)
    local depth = get_depth(this)
    local posX = get_positionX(this)
    local posY = get_positionY(this)
    local vel_x = get_velocity(this)

  
    if vel_x > 0 then
        current_direction = "right"
    elseif vel_x < 0 then
        current_direction = "left"
    end

    local obj_scaleT = (objective_scale * 10) / objective_depth
    local scaleT = (scale * 10) / depth

    local objective_moved = (
        last_objective_scaleT == nil or 
        math.abs(obj_scaleT - last_objective_scaleT) > 0.05
    )

    if not impulse_applied and objective_moved then
        local dy = (obj_scaleT - scaleT) * 20
        if math.abs(dy) > 1 then
            local dirY = dy / math.abs(dy)
            set_velocity(this, vel_x, dirY * 2.5)
            impulse_applied = true
            elapsed = 0
        end
    elseif elapsed >= impulse_duration then
        set_velocity(this, vel_x, 0)
        impulse_applied = false
    end

    last_objective_scaleT = obj_scaleT

    local anim = animations[current_direction]
    set_srcRect(this, anim.width, anim.height, anim.x, anim.y)
end