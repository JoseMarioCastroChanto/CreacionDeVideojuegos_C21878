local animations = {
    right = {x = 0, y = 0, width = 80, height = 40},
    left = {x = 0, y = 40, width = 80, height = 40} 
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