scene = {
    --Tabla de imagenes y sprites
    sprites = {
        [0]={assetId = "player", filePath = "./assets/images/playerAllDirections.png"},
        {assetId = "background", filePath = "./assets/images/Background.png"},
    },
   
    -- Tabla de fuentes
    fonts = {
       [0] = 
       {fontId = "press_start_32", filePath="./assets/fonts/press_start_2p.ttf", fontSize = 32},
       {fontId = "press_start_50", filePath="./assets/fonts/press_start_2p.ttf", fontSize = 50},
    },
   
    --Tabla de acciones y teclas
    keys ={
       [0]=
       {name = "up", key = 119},
       {name = "left", key = 97},
       {name = "down", key = 115},
       {name = "right", key = 100},
    },
   
    --Tabla de acciones y botones del raton
   buttons = {
       [0] =
       {name = "mouse_left_button", button = 1}
   
   },
   
   entities = {
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
    {
        components = {
            clickable = {},
            script = {
                path = "./assets/scripts/menu_button_01.lua",
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
    {
        components = {
            clickable = {},
            script = {
                path = "./assets/scripts/menu_button.lua",
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
                position = { x = 730.0, y = 400.0 }, 
                scale = { x = 1.0, y = 1.0 },
                rotation = 0.0
            }
        }
    },
    -- Player
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