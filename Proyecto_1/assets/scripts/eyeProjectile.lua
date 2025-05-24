local elapsed = 0
local impulse_duration = 1000 -- duración del impulso en milisegundos
local impulse_applied = false

function update()
    local dt = get_delta_time()
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

    local obj_scaleT = (objective_scale * 10) / objective_depth
    local scaleT = (scale * 10) / depth

    if not impulse_applied then
        if (scaleT - obj_scaleT) > 0 then
            set_velocity(this, vel_x, -5)
        elseif (scaleT - obj_scaleT) < 0 then
            set_velocity(this, vel_x, 5)
        end
        impulse_applied = true
        elapsed = 0 
    elseif impulse_applied and elapsed >= impulse_duration then
 
        set_velocity(this, vel_x, 0)
        impulse_applied = false  
    end
end