local animations = {
    right = {x = 0, y = 0, width = 60, height = 57},
    left = {x = 0, y = 57, width = 60, height = 57},
    rightAttack = {x = 0, y = 114, width = 60, height = 57}, 
    leftAttack = {x = 0, y = 171, width = 60, height = 57}, 
}



local tolerance = 500
local lastDir = "right"
local coolDown = 0
function update()
    objective_posX = search_objectiveX(this, false)
    posX = get_positionX(this)
    scale = get_scale(this)
    depth = get_depth(this)
    scaleT = (scale*10)/depth


    if math.abs(objective_posX - posX) <= tolerance then
        set_velocity(this,0,0)
        current_direction = lastDir;
            if coolDown <= 0 then
                if lastDir == "rightAttack" then
                    create_dynamic_entity(this,1,5,scaleT)
                else
                    create_dynamic_entity(this,-1,5,scaleT)
                end 
                coolDown = 3000
            end
            coolDown = coolDown - get_delta_time()

    end

    if get_velocity(this) > 0 then
        current_direction = "right"
        lastDir = "rightAttack"
    elseif get_velocity(this) < 0 then
        current_direction = "left"
        lastDir = "leftAttack"
    end

    local anim = animations[current_direction]
    set_srcRect(this, anim.width, anim.height, anim.x, anim.y)
end