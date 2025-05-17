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
            min_scale = 0,
            max_scale = 10,
            original_width = 0,
            scale_speed = 0, 
            reference = 0,

            
        },
    }
},
}