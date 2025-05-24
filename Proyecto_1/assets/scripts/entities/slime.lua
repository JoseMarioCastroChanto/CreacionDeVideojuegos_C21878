local animations = {
    right = {x = 0, y = 0, width = 32, height = 32},
    left  = {x = 0, y = 32, width = 32, height = 32},
    spin = {x = 0, y = 64, width = 32, height = 32}
}

local tolerance = 1
local scale_tolerance = 0.5
local haveToMove = false
local Back = false

function update()
    objective_posX = search_objectiveX(this, false)
    objective_posY = search_objectiveY(this, false)
    objective_scale = search_objectiveScale(this, false)
    objective_depth = search_objectiveDepth(this,false)
    scale = get_scale(this)
    depth = get_depth(this)
    posX = get_positionX(this)
    posY = get_positionY(this)

    obj_scaleT = (objective_scale*10)/objective_depth
    scaleT = (scale*10)/depth

    if math.abs(objective_posX - posX) <= tolerance and not haveToMove then
        if (scaleT-obj_scaleT) > 0  then
            set_velocity(this,0,-10)
        elseif (scaleT-obj_scaleT) < 0 then
            set_velocity(this,0,10)
            Back = true
        end
        haveToMove = true
    end

    if math.abs(scaleT-obj_scaleT) <= scale_tolerance and haveToMove and
    not Back then
        set_velocity(this,0,0)
    end

    if scaleT-obj_scaleT > scale_tolerance and haveToMove and Back then
        set_velocity(this,0,0)
    end

    if get_velocity(this) > 0 then
        current_direction = "right"
    elseif get_velocity(this) < 0 then
        current_direction = "left"
    else 
        current_direction = "spin" 
        set_numFrames(this, 8)
    end
    local anim = animations[current_direction]
    set_srcRect(this, anim.width, anim.height, anim.x, anim.y)
end