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
    lua.set_function("set_scale", SetScale);
    lua.set_function("set_position", SetPosition);
    lua.set_function("get_positionX", GetPositionX);
    lua.set_function("get_positionY", GetPositionY);
    lua.set_function("set_srcRect", SetSrcRect);
    lua.set_function("set_numFrames", SetNumFrames);
    lua.set_function("go_to_scene", GoToScene);
    lua.set_function("create_dynamic_entity",CreateDynamicEntity);
    lua.set_function("get_velocity", GetVelocity);
    lua.set_function("get_delta_time", GetDeltaTime);
    lua.set_function("get_time", GetTime);
    lua.set_function("get_defeat", GetDefeat);
    lua.set_function("set_timer", SetTimer);
    lua.set_function("set_text", SetText);
    lua.set_function("search_objectiveX", SearchObjectiveX);
    lua.set_function("search_objectiveY", SearchObjectiveY);
    lua.set_function("search_objectiveScale", SearchObjectiveScale);
    lua.set_function("search_objectiveDepth", SearchObjectiveDepth);
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