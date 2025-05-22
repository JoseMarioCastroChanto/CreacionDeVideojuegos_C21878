entities = {
    [0] = 
  -- Bomb
  {
    components = {
        animation = {
            numFrames = 6,
            frameSpeedRate = 5,
            isLoop = true,

          },
          circle_collider = {
            radius = 16,
            width = 32,
            height = 32,


          },

        rigidbody ={
            velocity = { x = 150, y = 0 },

        },
        script = {
            path = "./assets/scripts/bomb.lua",
        },
        sprite = {
            assetId = "bomb",
            width = 64,
            height = 64,
            src_rect = { x = 0, y = 0},

        },
        transform = {
            position = { x = 0.0, y = 0.0},
            scale = { x = 5.0, y = 5.0},
            rotation = 0.0

        },
        tagprojectile = {},
        life = {
            life_count = 1,

        },
        damage = {
            damage_dealt = 1,

        },
        depth = {
            min_scale = 0,
            max_scale = 5,
            original_width = 0,
            scale_speed = 0, 
            reference = 0,
            
        },
    }
},
  -- Slime_monster
  {
    components = {
        animation = {
            numFrames = 4,
            frameSpeedRate = 5,
            isLoop = true,

          },

          circle_collider = {
            radius = 8,
            width = 16,
            height = 16,


          },

        rigidbody ={
            velocity = { x = 50, y = 0 },

        },
        script = {
            path = "./assets/scripts/slime.lua",
        },
        sprite = {
            assetId = "slime",
            width = 32,
            height = 32,
            src_rect = { x = 0, y = 0},

        },
        transform = {
            position = { x = 0.0, y = 0.0},
            scale = { x = 10.0, y = 10.0},
            rotation = 0.0

        },
        tagenemy = {},
        life = {
            life_count = 1,

        },
        damage = {
            damage_dealt = 1,

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
  -- Eye_monster
  {
    components = {
        animation = {
            numFrames = 13,
            frameSpeedRate = 5,
            isLoop = true,

          },
          circle_collider = {
            radius = 1,
            width = 2,
            height = 2,
          },

          script = {
            path = "./assets/scripts/eye.lua",
        },

        rigidbody ={
            velocity = { x = 50, y = 0 },

        },
        sprite = {
            assetId = "eye",
            width = 60 ,
            height = 57,
            src_rect = { x = 0, y = 0},

        },
        transform = {
            position = { x = 0.0, y = 0.0},
            scale = { x = 1.0, y = 1.0},
            rotation = 0.0

        },
        tagenemy = {},
        life = {
            life_count = 3,

        },
        damage = {
            damage_dealt = 1,

        },
        depth = {
            min_scale = 2.8,
            max_scale = 7.0,
            original_width = 60.0,
            scale_speed = 0.2, 
            reference = 480,

            
        },
    }
},
     -- Night Borne
  {
    components = {
        animation = {
            numFrames = 6,
            frameSpeedRate = 5,
            isLoop = true,

          },
          circle_collider = {
            radius = 1,
            width = 2,
            height = 2,


          },

          script = {
            path = "./assets/scripts/nightborne.lua",
        },

        rigidbody ={
            velocity = { x = 50, y = 0 },

        },
        sprite = {
            assetId = "nightborne",
            width = 80,
            height = 40,
            src_rect = { x = 0, y = 40},

        },
        transform = {
            position = { x = 0.0, y = 0.0},
            scale = { x = 1.0, y = 1.0},
            rotation = 0.0

        },
        tagenemy = {},
        life = {
            life_count = 1,

        },
        damage = {
            damage_dealt = 1,

        },
        depth = {
            min_scale = 4.8,
            max_scale = 12,
            original_width = 80.0,
            scale_speed = 0.2, 
            reference = 480,

            
        },
    }
},
 -- Fire Totem
 {
    components = {
        animation = {
            numFrames = 14,
            frameSpeedRate = 8,
            isLoop = true,

          },

          circle_collider = {
            radius = 16,
            width = 32,
            height = 32,


          },

        rigidbody ={
            velocity = { x = 0, y = 0 },

        },
       
        sprite = {
            assetId = "totem",
            width = 64,
            height = 96,
            src_rect = { x = 0, y = 192},

        },
        transform = {
            position = { x = 650.0, y = 580.0},
            scale = { x = 2.5, y = 2.5},
            rotation = 0.0

        },
        tagprojectile = {},
        tagobjective = {},
        life = {
            life_count = 3,

        },
        damage = {
            damage_dealt = 3,

        },
        depth = {
            min_scale = 1,
            max_scale = 2.5,
            original_width = 0,
            scale_speed = 0, 
            reference = 0,
            
        },
    }
},

}