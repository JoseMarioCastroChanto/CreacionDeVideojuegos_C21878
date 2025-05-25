



local tolerance = 700
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
                if lastDir == "right" then
                    create_dynamic_entity(this,1,9,scale)
                else
                    create_dynamic_entity(this,-1,9,scale)
                end 
                coolDown = 8000
            end
            coolDown = coolDown - get_delta_time()

    end

    if get_velocity(this) > 0 then
        current_direction = "right"
        lastDir = "right"
    elseif get_velocity(this) < 0 then
        current_direction = "left"
        lastDir = "left"
    end
end