#ifndef SCRIPTSYSTEM_HPP
#define SCRIPTSYSTEM_HPP

#include <memory>
#include <sol/sol.hpp>

#include "../Binding/LuaBinding.hpp"
#include "../Components/ScriptComponent.hpp"
#include "../ECS/ECS.hpp"
class ScriptSystem : public System {
 public:
  ScriptSystem(){
    RequireComponent<ScriptComponent>();
  }

  void CreateLuaBinding(sol::state& lua){
    // Classes
    lua.new_usertype<Entity>("entity");

    // Functions
    lua.set_function("is_action_activated", IsActionActivated);
    lua.set_function("set_velocity", SetVelocity);
    lua.set_function("get_scale", GetScale);
    lua.set_function("set_position", SetPosition);
    lua.set_function("get_positionX", GetPositionX);
    lua.set_function("get_positionY", GetPositionY);
    lua.set_function("set_srcRect", SetSrcRect);
    lua.set_function("set_numFrames", SetNumFrames);
    lua.set_function("go_to_scene", GoToScene);
  }

  void Update(sol::state& lua){
    for(auto entity : GetSystemEntities()){
        const auto& script = entity.GetComponent<ScriptComponent>();

        if(script.update != sol::lua_nil){
            lua["this"] = entity;
            script.update();
        }
    }
  }
};
#endif