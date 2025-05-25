function update()
    if get_time() >= 130000 then
        go_to_scene("Win_3")
    end 
    if get_defeat() then
        go_to_scene("Defeat_3")
    end 
end