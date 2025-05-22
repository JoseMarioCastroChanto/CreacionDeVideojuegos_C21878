scene = {
 --Tabla de imagenes y sprites
 sprites = {
    [0]=
    {assetId = "trees", filePath = "./assets/images/Trees.png"},
    {assetId = "grass", filePath = "./assets/images/grass.png"},
    {assetId = "bomb", filePath = "./assets/images/Bomb.png"},
    {assetId = "slime", filePath = "./assets/images/Slime.png"},
    {assetId = "eye", filePath = "./assets/images/Eye.png"},
    {assetId = "nightborne", filePath = "./assets/images/NightBorne.png"},
    {assetId = "background", filePath = "./assets/images/Background.png"},
    {assetId = "player", filePath = "./assets/images/playerAllDirections.png"},
    {assetId = "obelisk", filePath = "./assets/images/Obelisk.png"},
    {assetId = "totem", filePath = "./assets/images/FireTotem.png"}
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
    {name = "k", key = 107},
    {name = "l", key = 108},
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

    -- Monster Spawner A
    {
        components = {
            transform = {
                position = { x = -250.0, y = 480.0},
                scale = { x = 4, y = 4},
                rotation = 0.0

            },
            script = {
                path = "./assets/scripts/spawners/scene_01_Spawners_A.lua",
            },
            entitySpawner = {
                is_player = false
  
              },
        }
    },
-- Monster Spawner B
{
    components = {
        transform = {
            position = { x = -250.0, y = 480.0},
            scale = { x = 5, y = 5},
            rotation = 0.0

        },
        script = {
            path = "./assets/scripts/spawners/scene_01_Spawners_B.lua",
        },
        entitySpawner = {
            is_player = false

          },
    }
},
-- Monster Spawner C
{
    components = {
        transform = {
            position = { x = -250.0, y = 480.0},
            scale = { x = 6, y = 6},
            rotation = 0.0

        },
        script = {
            path = "./assets/scripts/spawners/scene_01_Spawners_C.lua",
        },
        entitySpawner = {
            is_player = false

          },
    }
},

-- Monster Spawner D
{
    components = {
        transform = {
            position = { x = -250.0, y = 480.0},
            scale = { x = 7, y = 7},
            rotation = 0.0

        },
        script = {
            path = "./assets/scripts/spawners/scene_01_Spawners_D.lua",
        },
        entitySpawner = {
            is_player = false

          },
    }
},

-- Monster Spawner E
{
    components = {
        transform = {
            position = { x = -250.0, y = 480.0},
            scale = { x = 8, y = 8},
            rotation = 0.0

        },
        script = {
            path = "./assets/scripts/spawners/scene_01_Spawners_E.lua",
        },
        entitySpawner = {
            is_player = false

          },
    }
},
-- Monster Spawner F
{
    components = {
        transform = {
            position = { x = -250.0, y = 480.0},
            scale = { x = 9, y = 9},
            rotation = 0.0

        },
        script = {
            path = "./assets/scripts/spawners/scene_01_Spawners_F.lua",
        },
        entitySpawner = {
            is_player = false

          },
    }
},
-- Monster Spawner G
{
    components = {
        transform = {
            position = { x = -250.0, y = 480.0},
            scale = { x = 10, y = 10},
            rotation = 0.0

        },
        script = {
            path = "./assets/scripts/spawners/scene_01_Spawners_G.lua",
        },
        entitySpawner = {
            is_player = false

          },
    }
},

    -- Monster Spawner A1
    {
        components = {
            transform = {
                position = { x = 1650.0, y = 480.0},
                scale = { x = 4, y = 4},
                rotation = 0.0

            },
            script = {
                path = "./assets/scripts/spawners/scene_01_Spawners_A1.lua",
            },
            entitySpawner = {
                is_player = false
  
              },
        }
    },
-- Monster Spawner B1
{
    components = {
        transform = {
            position = { x = 1650.0, y = 480.0},
            scale = { x = 5, y = 5},
            rotation = 0.0

        },
        script = {
            path = "./assets/scripts/spawners/scene_01_Spawners_B1.lua",
        },
        entitySpawner = {
            is_player = false

          },
    }
},
-- Monster Spawner C1
{
    components = {
        transform = {
            position = { x = 1650.0, y = 480.0},
            scale = { x = 6, y = 6},
            rotation = 0.0

        },
        script = {
            path = "./assets/scripts/spawners/scene_01_Spawners_C1.lua",
        },
        entitySpawner = {
            is_player = false

          },
    }
},

-- Monster Spawner D1
{
    components = {
        transform = {
            position = { x = 1650.0, y = 480.0},
            scale = { x = 7, y = 7},
            rotation = 0.0

        },
        script = {
            path = "./assets/scripts/spawners/scene_01_Spawners_D1.lua",
        },
        entitySpawner = {
            is_player = false

          },
    }
},

-- Monster Spawner E1
{
    components = {
        transform = {
            position = { x = 1650.0, y = 480.0},
            scale = { x = 8, y = 8},
            rotation = 0.0

        },
        script = {
            path = "./assets/scripts/spawners/scene_01_Spawners_E1.lua",
        },
        entitySpawner = {
            is_player = false

          },
    }
},

-- Monster Spawner F1
{
    components = {
        transform = {
            position = { x = 1650.0, y = 480.0},
            scale = { x = 9, y = 9},
            rotation = 0.0

        },
        script = {
            path = "./assets/scripts/spawners/scene_01_Spawners_F1.lua",
        },
        entitySpawner = {
            is_player = false

          },
    }
},

-- Monster Spawner G1
{
    components = {
        transform = {
            position = { x = 1650.0, y = 480.0},
            scale = { x = 10, y = 10},
            rotation = 0.0

        },
        script = {
            path = "./assets/scripts/spawners/scene_01_Spawners_G1.lua",
        },
        entitySpawner = {
            is_player = false

          },
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
            entitySpawner = {
                is_player = true
  
              },
            tagobjective = {},
            tagplayer = {},
            life = {
                life_count = 2,

            },
        }
    },
     -- Obelisk
     {
        components = {
            animation = {
                numFrames = 14,
                frameSpeedRate = 5,
                isLoop = true,
  
              },
            sprite = {
                assetId = "obelisk",
                width = 190,
                height = 240,
                src_rect = { x = 0, y = 0},

            },
            depth = {
                min_scale = 0,
                max_scale = 2,
                original_width = 0,
                scale_speed = 0, 
                reference = 0,
                
            },
            transform = {
                position = { x = 650.0, y = 380.0},
                scale = { x = 1.4, y = 1.4},
                rotation = 0.0

            },
        }
    },
    --Objective
    {
        components = {
            circle_collider = {
                radius = 8,  
                width = 16,   
                height = 16 
            },
            transform = {
                position = { x = 680.0, y = 500.0},
                scale = { x = 7, y = 7},
                rotation = 0.0

            },
            depth = {
                min_scale = 0,
                max_scale = 10,
                original_width = 0,
                scale_speed = 0, 
                reference = 0,
                
            },
            tagobjective = {},
            life = {
                life_count = 80,

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
   -- Timer
   {
    components = {
        script={
            path = "./assets/scripts/timer.lua",
        },
        text = {
            text = "0",
            fontId = "press_start_24",
            r = 0,
            g = 0,
            b = 0,
            a = 0
        },
        transform = {
            position = { x = 1420.0, y = 50.0},
            scale = { x = 1.0, y = 1.0},
            rotation = 0.0

        }
    }
}, 
   -- Time Text
   {
    components = {
        text = {
            text = "TIME:  /60",
            fontId = "press_start_24",
            r = 0,
            g = 0,
            b = 0,
            a = 0
        },
        transform = {
            position = { x = 1300.0, y = 50.0},
            scale = { x = 1.0, y = 1.0},
            rotation = 0.0

        }
    }
}, 

   -- Big Bomb Stock
   {
    components = {
        script={
            path = "./assets/scripts/bigBombStock.lua",
        },
        text = {
            text = "0",
            fontId = "press_start_24",
            r = 150,
            g = 0,
            b = 0,
            a = 0
        },
        transform = {
            position = { x = 1230.0, y = 50.0},
            scale = { x = 1.0, y = 1.0},
            rotation = 0.0

        }
    }
}, 
   -- Big Bomb Text
   {
    components = {
        text = {
            text = "Big Bomb: ",
            fontId = "press_start_24",
            r = 150,
            g = 0,
            b = 0,
            a = 0
        },
        transform = {
            position = { x = 1000.0, y = 50.0},
            scale = { x = 1.0, y = 1.0},
            rotation = 0.0

        }
    }
}, 


   -- Controller
   {
    components = {
        script={
            path = "./assets/scripts/gameController.lua",
        },
    }
}, 
  }
}
