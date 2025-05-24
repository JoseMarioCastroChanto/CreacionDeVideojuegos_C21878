scene = {
    --Tabla de imagenes y sprites
    sprites = {
        [0]={assetId = "player", filePath = "./assets/images/playerAllDirections.png"},
        {assetId = "hud", filePath = "./assets/images/HUDBox.png"},
    },
   
    -- Tabla de fuentes
    fonts = {
       [0] = 
       {fontId = "press_start_32", filePath="./assets/fonts/press_start_2p.ttf", fontSize = 32},
       {fontId = "press_start_50", filePath="./assets/fonts/press_start_2p.ttf", fontSize = 50},
    },
    music = {
        [0] =  { musicId = "win", filePath = "./assets/audio/win.mp3" }
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
                text = "YOU WIN",
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
                position = { x = 630, y = 370},
                scale = { x = 0.5, y = 0.5},
                rotation = 0.0

            },
        }
    },
        
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
    -- Player
    {
        components = {
            animation = {
                numFrames = 2,
                frameSpeedRate = 5,
                isLoop = true,
  
              },
            sprite = {
                assetId = "player",
                width = 32,
                height = 32,
                src_rect = { x = 0, y = 192},

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