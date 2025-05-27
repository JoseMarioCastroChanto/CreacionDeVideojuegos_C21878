#ifndef ECS_HPP
#define ECS_HPP

#include <bitset>
#include <cstddef>
#include <deque>
#include <iostream>
#include <memory>
#include <set>
#include <typeindex>
#include <vector>
#include <unordered_map>
#include "../Utils/Pool.hpp"

/**
 * @brief Maximum number of components supported by the ECS.
 */
const unsigned int MAX_COMPONENTS = 64;

/**
 * @brief Signature type used to represent the set of components an entity has.
 * Uses a bitset of MAX_COMPONENTS size.
 */
// Signature
typedef std::bitset<MAX_COMPONENTS> Signature;

/**
 * @brief Base class for all components to generate unique IDs.
 */
struct IComponent {
 protected:
  /// Next available component ID.
  static int nextId;
};

/**
 * @brief Template to generate unique component IDs per component type.
 * @tparam TComponent The component type.
 */
template <typename TComponent>
class Component : public IComponent {
 public:
  /**
   * @brief Returns the unique ID associated with this component type.
   * @return Unique component ID.
   */
 static int GetId(){
    static int id = nextId++;
    return id;
 }
};

/**
 * @class Entity
 * @brief Represents an entity in the ECS, identified by a unique ID.
 */
class Entity{
 private:
 /// Unique ID of the entity.
  int id;

 public:
  /**
   * @brief Constructs an entity with the given ID.
   * @param id Unique identifier for the entity.
   */
  Entity(int id): id(id){}
   /**
   * @brief Returns the unique ID of the entity.
   * @return The entity ID.
   */
  int GetId() const;
   /**
   * @brief Marks this entity for removal.
   */
  void Kill();

  // Comparison operators based on entity ID.
  bool operator ==(const Entity& other) const {return id == other.id; }
  bool operator !=(const Entity& other) const {return id != other.id; }
  bool operator >(const Entity& other) const {return id > other.id; }
  bool operator <(const Entity& other) const {return id < other.id; }
  
  /**
   * @brief Adds a component of type TComponent to the entity.
   * @tparam TComponent The component type.
   * @tparam TArgs Constructor arguments for the component.
   * @param args Arguments to forward to the component's constructor.
   */
  template <typename TComponent, typename... TArgs>
  void AddComponent(TArgs&&... args);
  
  /**
   * @brief Removes a component of type TComponent from the entity.
   * @tparam TComponent The component type to remove.
   */
  template <typename TComponent>
  void RemoveComponent();
  
   /**
   * @brief Checks if the entity has a component of type TComponent.
   * @tparam TComponent The component type to check.
   * @return True if the entity has the component, false otherwise.
   */
  template <typename TComponent>
  bool HasComponent() const;

   /**
   * @brief Returns a reference to the component of type TComponent.
   * @tparam TComponent The component type.
   * @return Reference to the component instance.
   */  
  template <typename TComponent>
  TComponent& GetComponent() const;
  
  /// Pointer to the registry managing this entity.
  class Registry* registry;
};

/**
 * @class System
 * @brief Base class for systems that operate on entities with specific components.
 */
class System{
 private:
  /// Signature representing the required components for this system.
  Signature componentSignature;
  /// List of entities currently managed by this system.
  std::vector<Entity> entities;

public:
 System() = default;
 ~System() = default;
 
  /**
   * @brief Adds an entity to this system.
   * @param entity The entity to add.
   */
 void AddEntityToSystem(Entity entity);

 /**
   * @brief Removes an entity from this system.
   * @param entity The entity to remove.
   */
 void RemoveEntityFromSystem(Entity entity);

 /**
   * @brief Returns all entities currently registered in this system.
   * @return Vector of entities.
   */
 std::vector<Entity> GetSystemEntities() const;

 /**
   * @brief Returns the component signature required by this system.
   * @return Component signature bitset.
   */
 const Signature& GetComponentSignature() const;

 /**
   * @brief Adds a required component type to the system's signature.
   * @tparam TComponent The component type required.
   */
 template <typename TComponent>
 void RequireComponent();
 
};

/**
 * @class Registry
 * @brief Manages entities, components, and systems in the ECS.
 */
class Registry {
 private:
  /// Number of entities currently created.
  int numEntity = 0;

  /// Pools storing components indexed by component ID.
  std::vector<std::shared_ptr<IPool>> componentsPools;
  /// Signatures of each entity indicating which components they have.
  std::vector<Signature> entityComponentSignatures;
  
  /// Systems managed by the registry indexed by type.
  std::unordered_map<std::type_index, std::shared_ptr<System>> systems;

   /// Entities pending addition.
  std::set<Entity> entitiesToBeAdded;
  /// Entities pending removal.
  std::set<Entity> entitiesToBeKilled;
  
  /// Queue of free entity IDs for reuse.
  std::deque<int> freeIds;
   /**
   * @brief Removes all components of a given entity.
   * @param entity The entity whose components to remove.
   */
  void RemoveAllComponentsOfEntity(Entity entity);

  public:
   Registry();
   ~Registry();
   

  /**
   * @brief Processes entity addition and removal, updating systems accordingly.
   */
   void Update();

   //Entity Managment

   /**
   * @brief Creates and returns a new entity.
   * @return The newly created entity.
   */
   Entity CreateEntity();
   /**
   * @brief Marks an entity for removal.
   * @param entity The entity to kill.
   */
   void KillEntity(Entity entity);

   //Component Managment

     /**
   * @brief Adds a component of type TComponent to an entity.
   * @tparam TComponent The component type.
   * @tparam TArgs Arguments to forward to the component's constructor.
   * @param entity The entity to add the component to.
   * @param args Constructor arguments for the component.
   */
   template <typename TComponent, typename... TArgs>
   void AddComponent(Entity entity, TArgs&&... args);
   
   /**
   * @brief Removes a component of type TComponent from an entity.
   * @tparam TComponent The component type.
   * @param entity The entity to remove the component from.
   */
   template <typename TComponent>
   void RemoveComponent(Entity entity);
   
    /**
   * @brief Checks if an entity has a component of type TComponent.
   * @tparam TComponent The component type.
   * @param entity The entity to check.
   * @return True if the entity has the component, false otherwise.
   */
   template <typename TComponent>
   bool HasComponent(Entity entity) const;

   /**
   * @brief Returns a reference to the component of type TComponent attached to an entity.
   * @tparam TComponent The component type.
   * @param entity The entity.
   * @return Reference to the component.
   */  
   template <typename TComponent>
   TComponent& GetComponent(Entity entity) const;

    //System Managment

   
  /**
   * @brief Adds a system of type TSystem to the registry.
   * @tparam TSystem The system type.
   * @tparam TArgs Arguments to forward to the system's constructor.
   * @param args Constructor arguments for the system.
   */ 
   template <typename TSystem, typename... TArgs>
   void AddSystem(TArgs&&... args);
   
   /**
   * @brief Removes a system of type TSystem from the registry.
   * @tparam TSystem The system type.
   */
   template <typename TSystem>
   void RemoveSystem();
   
    /**
   * @brief Checks if a system of type TSystem is registered.
   * @tparam TSystem The system type.
   * @return True if the system is present, false otherwise.
   */
   template <typename TSystem>
   bool HasSystem() const;
   
   /**
   * @brief Returns a reference to the system of type TSystem.
   * @tparam TSystem The system type.
   * @return Reference to the system.
   */
   template <typename TSystem>
   TSystem& GetSystem() const;

   // Add and remove entities to systems

   /**
   * @brief Adds an entity to all systems whose signatures match the entity's components.
   * @param entity The entity to add.
   */
   void AddEntityToSystems(Entity entity);

   /**
   * @brief Removes an entity from all systems.
   * @param entity The entity to remove.
   */
   void RemoveEntityFromSystems(Entity entity);

   //Reset registry


  /**
   * @brief Removes all entities and clears the registry.
   */
   void ClearAllEntities();


};


template <typename TComponent>
void System::RequireComponent(){
  const auto componentId = Component<TComponent>::GetId();
  componentSignature.set(componentId);
}

template <typename TComponent, typename... TArgs>
void Registry::AddComponent(Entity entity, TArgs&&... args){
    const int componentId = Component<TComponent>::GetId();
    const int entityId = entity.GetId();

    if(static_cast<long unsigned int>(componentId) >= componentsPools.size()){
        componentsPools.resize(componentId + 10, nullptr);
    }

    if(!componentsPools[componentId]){
        std::shared_ptr<Pool<TComponent>> newComponentPool 
        = std::make_shared<Pool<TComponent>>();
        componentsPools[componentId] = newComponentPool;
    }

    std::shared_ptr<Pool<TComponent>> componentPool 
      = std::static_pointer_cast<Pool<TComponent>>(componentsPools[componentId]);
    
    if(entityId >= componentPool->GetSize()){
        componentPool->Resize(numEntity + 100);
    }

    TComponent newComponent(std::forward<TArgs>(args)...);

    componentPool->Set(entityId, newComponent);
    entityComponentSignatures[entityId].set(componentId);

    std::cout << "[Registry] Se agrega componente "<<componentId
    <<" a la entidad "<< entityId <<std::endl;
}

template <typename TComponent>
void Registry::RemoveComponent(Entity entity){
    const int componentId = Component<TComponent>::GetId();
    const int entityId = entity.GetId();
    
    entityComponentSignatures[entityId].set(componentId, false);
}

template <typename TComponent>
bool Registry::HasComponent(Entity entity) const{
    const int componentId = Component<TComponent>::GetId();
    const int entityId = entity.GetId();

    return entityComponentSignatures[entityId].test(componentId);
}

template <typename TComponent>
TComponent& Registry::GetComponent(Entity entity) const{
    const int componentId = Component<TComponent>::GetId();
    const int entityId = entity.GetId();

    auto componentPool 
     = std::static_pointer_cast<Pool<TComponent>>(componentsPools[componentId]);

    return componentPool->Get(entityId);
}

template <typename TSystem, typename... TArgs>
void Registry::AddSystem(TArgs&&... args){
    std::shared_ptr<TSystem>  newSystem 
     = std::make_shared<TSystem>(std::forward<TArgs>(args)...);
    systems.insert(std::make_pair(std::type_index(typeid(TSystem)), newSystem));
}

template <typename TSystem>
void Registry::RemoveSystem(){
    auto system = system.find(std::type_index(typeid(TSystem)));
    systems.erase(system);
}

template <typename TSystem>
bool Registry::HasSystem() const{
    return systems.find(std::type_index(typeid(TSystem))) != systems.end();

}
   
template <typename TSystem>
TSystem& Registry::GetSystem() const{
    auto system = systems.find(std::type_index(typeid(TSystem)));
    return *(std::static_pointer_cast<TSystem>(system->second));

}

template <typename TComponent, typename... TArgs>
void Entity::AddComponent(TArgs&&... args){
    registry->AddComponent<TComponent>(*this, std::forward<TArgs>(args)...);
}

template <typename TComponent>
void Entity::RemoveComponent(){
    registry->RemoveComponent<TComponent>(*this);
}

template <typename TComponent>
bool Entity::HasComponent() const{
    return registry->HasComponent<TComponent>(*this);
}
   
template <typename TComponent>
TComponent& Entity::GetComponent() const{
    return registry->GetComponent<TComponent>(*this);
}


#endif