local animations = {
    right = {x = 0, y = 0, width = 60, height = 57},
    left = {x = 0, y = 57, width = 60, height = 57} 
}


function update()
    if get_velocity(this) > 0 then
        current_direction = "right"
    else
        current_direction = "left"
    end
    local anim = animations[current_direction]
    set_srcRect(this, anim.width, anim.height, anim.x, anim.y)
end