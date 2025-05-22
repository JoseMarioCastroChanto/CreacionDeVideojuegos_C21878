function update()
    if get_time() >= 60000 then
        go_to_scene("Win_1")
    end 
    if get_defeat() then
        go_to_scene("Defeat_1")
    end 
end