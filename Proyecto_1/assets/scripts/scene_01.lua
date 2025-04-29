scene = {
 --Tabla de imagenes y sprites
 sprites = {
    [0]=
    {assetId = "trees", filePath = "./assets/images/Trees.png"},
    {assetId = "grass", filePath = "./assets/images/grass.png"},
    {assetId = "grass1", filePath = "./assets/images/grass1.png"},
    {assetId = "background", filePath = "./assets/images/Background.png"},
    {assetId = "player", filePath = "./assets/images/playerAllDirections.png"}
 },

 -- Tabla de fuentes
 fonts = {
    [0] = 
    {fontId = "press_start_24", filePath="./assets/fonts/press_start_2p.ttf", fontSize = 24},
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

 --Tabla de entidades
 entities = {
    [0] = 

     -- Background
     {
        components = {
            sprite = {
                assetId = "background",
                width = 2300,
                height = 885,
                src_rect = { x = 0, y = 0},

            },
            transform = {
                position = { x = 0.0, y = 0.0},
                scale = { x = 0.7, y = 0.7},
                rotation = 0.0

            },
        }
    },
    {
        components = {
            sprite = {
                assetId = "grass",
                width = 1600,
                height = 900,
                src_rect = { x = 0, y = 0},

            },
            transform = {
                position = { x = 100.0, y = -250.0},
                scale = { x = 1, y = 1},
                rotation = 0.0

            },
        }
    },
    {
        components = {
            sprite = {
                assetId = "grass",
                width = 1600,
                height = 900,
                src_rect = { x = 0, y = 0},

            },
            transform = {
                position = { x = -270.0, y = -250.0},
                scale = { x = 1, y = 1},
                rotation = 0.0

            },
        }
    },
    {
        components = {
            sprite = {
                assetId = "grass",
                width = 1600,
                height = 900,
                src_rect = { x = 0, y = 0},

            },
            transform = {
                position = { x = -225.0, y = -200.0},
                scale = { x = 1, y = 1},
                rotation = 0.0

            },
        }
    },
    {
        components = {
            sprite = {
                assetId = "grass",
                width = 1600,
                height = 900,
                src_rect = { x = 0, y = 0},

            },
            transform = {
                position = { x = 25.0, y = -200.0},
                scale = { x = 1, y = 1},
                rotation = 0.0

            },
        }
    },
    {
        components = {
            sprite = {
                assetId = "grass",
                width = 1600,
                height = 900,
                src_rect = { x = 0, y = 0},

            },
            transform = {
                position = { x = -265.0, y = -150.0},
                scale = { x = 1, y = 1},
                rotation = 0.0

            },
        }
    },
    {
        components = {
            sprite = {
                assetId = "grass",
                width = 1600,
                height = 900,
                src_rect = { x = 0, y = 0},

            },
            transform = {
                position = { x = 65.0, y = -150.0},
                scale = { x = 1, y = 1},
                rotation = 0.0

            },
        }
    },
    {
        components = {
            sprite = {
                assetId = "grass",
                width = 1600,
                height = 900,
                src_rect = { x = 0, y = 0},

            },
            transform = {
                position = { x = -205.0, y = -150.0},
                scale = { x = 1, y = 1},
                rotation = 0.0

            },
        }
    },
    
    
      {
        components = {
            sprite = {
                assetId = "grass",
                width = 1600,
                height = 900,
                src_rect = { x = 0, y = 0},

            },
            transform = {
                position = { x = 70.0, y = -100.0},
                scale = { x = 1, y = 1},
                rotation = 0.0

            },
        }
    },
    {
        components = {
            sprite = {
                assetId = "grass",
                width = 1600,
                height = 900,
                src_rect = { x = 0, y = 0},

            },
            transform = {
                position = { x = -150.0, y = -100.0},
                scale = { x = 1, y = 1},
                rotation = 0.0

            },
        }
    },
    
    
    {
        components = {
            sprite = {
                assetId = "grass",
                width = 1600,
                height = 900,
                src_rect = { x = 0, y = 0},

            },
            transform = {
                position = { x = 200.0, y = -50.0},
                scale = { x = 1, y = 1},
                rotation = 0.0

            },
        }
    },
    {
        components = {
            sprite = {
                assetId = "grass",
                width = 1600,
                height = 900,
                src_rect = { x = 0, y = 0},

            },
            transform = {
                position = { x = -100.0, y = -50.0},
                scale = { x = 1, y = 1},
                rotation = 0.0

            },
        }
    },
    
    -- Player
    {
        components = {
            animation = {
                numFrames = 2,
                frameSpeedRate = 3,
                isLoop = true,
  
              },
            circle_collider = {
              radius = 8,
              width = 16,
              height = 16,


            },
            rigidbody ={
                velocity = { x = 0, y = 0 },

            },
            script = {
                path = "./assets/scripts/player.lua",
            },
            sprite = {
                assetId = "player",
                width = 32,
                height = 32,
                src_rect = { x = 0, y = 0},

            },
            transform = {
                position = { x = 650.0, y = 580.0},
                scale = { x = 10.0, y = 10.0},
                rotation = 0.0

            },
            depth = {
                min_scale = 4.0,
                max_scale = 10.0,
                original_width = 32.0,
                scale_speed = 0.2, 
                reference = 580,
                
            },
        }
    },

     -- Grass
     {
        components = {
            sprite = {
                assetId = "grass",
                width = 1600,
                height = 900,
                src_rect = { x = 0, y = 0},

            },
            transform = {
                position = { x = 0.0, y = 0.0},
                scale = { x = 1, y = 1},
                rotation = 0.0

            },
        }
    },
    

   
-- Back Wall
{
    components = {
        tagwall = {},


        polygon_collider = {
             [0]= { x = -500, y = 0 },  
                { x = 1900, y = 0 },   
                { x = -500, y = 470 }, 
                { x = 1900, y = 470 }, 
         
        },

        transform = {
            position = { x = 0.0, y = 0.0},
            scale = { x = 1.0, y = 1.0},
            rotation = 0.0

        },
    }
},

-- Front Wall
{
    components = {
        tagwall = {},


        polygon_collider = {
             [0]= { x = -500, y = 900 },  
                { x = 1900, y = 900 },   
                { x = -500, y = 750 }, 
                { x = 1900, y = 750 }, 
         
        },

        transform = {
            position = { x = 0.0, y = 0.0},
            scale = { x = 1.0, y = 1.0},
            rotation = 0.0

        },
    }
},
 
  }
}