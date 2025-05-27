scene = {

    sprites = {
        [0]={assetId = "player", filePath = "./assets/images/playerAllDirections.png"},
        {assetId = "hud", filePath = "./assets/images/HUDBox.png"},
    },
   

    fonts = {
       [0] = 
       {fontId = "press_start_32", filePath="./assets/fonts/press_start_2p.ttf", fontSize = 32},
       {fontId = "press_start_50", filePath="./assets/fonts/press_start_2p.ttf", fontSize = 50},
       {fontId = "press_start_24", filePath="./assets/fonts/press_start_2p.ttf", fontSize = 24},
    },
    music = {
        [0] =  { musicId = "defeat", filePath = "./assets/audio/defeat.mp3" }
    },
   

    keys ={
       [0]=
       {name = "up", key = 119},
       {name = "left", key = 97},
       {name = "down", key = 115},
       {name = "right", key = 100},
    },
   

   buttons = {
       [0] =
       {name = "mouse_left_button", button = 1}
   
   },
   
   entities = {
    -- You Lose text
    [0] = {
        
        components = {
            clickable = {},
            text = {
                text = "YOU LOSE",
                fontId = "press_start_50",
                r = 200,
                g = 20,
                b = 120,
                a = 255
            },
            transform = {
                position = { x = 605.0, y = 50.0 }, 
                scale = { x = 1.0, y = 1.0 },
                rotation = 0.0
            }
        }
    },
    --HUD
    {
        components = {
            sprite = {
                assetId = "hud",
                width = 699,
                height = 233,
                src_rect = { x = 0, y = 0},

            },
            transform = {
                position = { x = 630, y = 250},
                scale = { x = 0.5, y = 0.5},
                rotation = 0.0

            },
        }
    },
     --HUD
     {
        components = {
            sprite = {
                assetId = "hud",
                width = 699,
                height = 233,
                src_rect = { x = 0, y = 0},

            },
            transform = {
                position = { x = 630, y = 370},
                scale = { x = 0.5, y = 0.5},
                rotation = 0.0

            },
        }
    },
    -- Try Again text
    {
        components = {
            clickable = {},
            script = {
                path = "./assets/scripts/buttons/menu_button_01.lua",
            },
            text = {
                text = "Try Again?",
                fontId = "press_start_32",
                r = 70,
                g = 130,
                b = 180,
                a = 255
            },
            transform = {
                position = { x = 645.0, y = 300.0 }, 
                scale = { x = 1.0, y = 1.0 },
                rotation = 0.0
            }
        }
    },
    -- Menu text
    {
        components = {
            clickable = {},
            script = {
                path = "./assets/scripts/buttons/menu_button.lua",
            },
            text = {
                text = "Menu",
                fontId = "press_start_32",
                r = 70,
                g = 130,
                b = 180,
                a = 255
            },
            transform = {
                position = { x = 740.0, y = 410.0 }, 
                scale = { x = 1.0, y = 1.0 },
                rotation = 0.0
            }
        }
    },
    -- Player Animation
    {
        components = {
            animation = {
                numFrames = 3,
                frameSpeedRate = 5,
                isLoop = true,
  
              },
            sprite = {
                assetId = "player",
                width = 32,
                height = 32,
                src_rect = { x = 0, y = 288},

            },
            transform = {
                position = { x = 490.0, y = 380.0},
                scale = { x = 20.0, y = 20.0},
                rotation = 0.0

            },
        }
    },
     }
   }