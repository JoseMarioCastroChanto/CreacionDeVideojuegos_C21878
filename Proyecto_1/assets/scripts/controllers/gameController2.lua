function update()
    if get_time() >= 95000 then
        go_to_scene("Win_2")
    end 
    if get_defeat() then
        go_to_scene("Defeat_2")
    end 
end