local tolerance = 700
local lastDir = "right"
local coolDown = 0
math.randomseed(123)
function update()
    objective_posX = search_objectiveX(this, false)
    posX = get_positionX(this)
    scale = get_scale(this)
    depth = get_depth(this)
    scaleT = (scale*10)/depth


    if math.abs(objective_posX - posX) <= tolerance then
        set_velocity(this,0,0)
        current_direction = lastDir;
        local opciones = {1, 3, 6}
        local prob = opciones[math.random(#opciones)]
            if coolDown <= 0 then
                if lastDir == "right" then
                    if prob == 1 then
                        create_dynamic_entity(this,1,prob,scaleT)
                    else
                        create_dynamic_entity(this,1,prob,scale)
                    end
                else
                    if prob == 1 then
                        create_dynamic_entity(this,-1,prob,scaleT)
                    else
                        create_dynamic_entity(this,-1,prob,scale)
                    end
                end 
                coolDown = 5000
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