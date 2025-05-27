#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <functional>
#include <list>
#include <map>
#include <memory>
#include <typeindex>
#include <iostream>
#include "Event.hpp"


/**
 * @brief Abstract interface for event callback handlers.
 */
class IEventCallback {
  private:
   /**
   * @brief Calls the stored callback with the given event.
   * @param e Reference to the event to process.
   */
   virtual void Call(Event& e) = 0;
  
  public:
  /**
   * @brief Virtual destructor.
   */
   virtual ~IEventCallback() = default;
  /**
   * @brief Executes the callback with the given event.
   * @param e Reference to the event to handle.
   */
   void Execute(Event& e){
    Call(e);
   }
};

/**
 * @brief Template event callback handler connecting an owner and event type.
 * 
 * @tparam TOwner Class type of the owner handling the event.
 * @tparam TEvent Event type to handle.
 */
template <typename TOwner, typename TEvent>
class EventCallback: public IEventCallback {
 private:
  typedef void (TOwner::*CallbackFunction)(TEvent&);

  TOwner* ownerInstance;///< Pointer to the owner instance.
  CallbackFunction callbackFunction;///< Member function pointer to the callback.
  
  /**
   * @brief Calls the owner callback with the event, casting it to TEvent.
   * @param e Reference to the base Event to cast and pass.
   */
  virtual void Call(Event& e) override {
    std::invoke(callbackFunction, ownerInstance, static_cast<TEvent&>(e));
  }

  public:
   /**
   * @brief Constructs the callback handler with owner and function pointer.
   * @param ownerInstance Pointer to the owner object.
   * @param callbackFunction Member function pointer to call on event.
   */
  EventCallback(TOwner* ownerInstance, CallbackFunction callbackFunction){
    this->callbackFunction = callbackFunction;
    this->ownerInstance = ownerInstance;
  }
};

typedef std::list<std::unique_ptr<IEventCallback>> HandlerList;

/**
 * @brief Manages event subscription and emission.
 * 
 * Allows objects to subscribe member functions to specific event types
 * and emits events to all registered subscribers.
 */
class EventManager {
 private:
  std::map<std::type_index, std::unique_ptr<HandlerList>> subscribers;

 public:
  /**
   * @brief Constructs an EventManager.
   */
  EventManager(){
    std::cout<< "[EventManager] Se ejecuta constructor" << std::endl;
  }

  /**
   * @brief Destructor.
   */
 ~EventManager(){
    std::cout<< "[EventManager] Se ejecuta destructor" << std::endl;
  }
  

  /**
   * @brief Clears all subscribers, effectively unsubscribing all.
   */
  void Reset(){
    subscribers.clear();
  }
  
  /**
   * @brief Subscribes a member function of an owner to a specific event type.
   * 
   * @tparam TEvent The event type to subscribe to.
   * @tparam TOwner The class type of the owner handling the event.
   * @param ownerInstance Pointer to the owner instance.
   * @param callbackFunction Member function pointer to the callback.
   */
  template <typename TEvent, typename TOwner>
  void SubscribeToEvent(TOwner* ownerInstance,
  void (TOwner::*callbackFunction)(TEvent&)) {
    if(!subscribers[typeid(TEvent)].get()){
        subscribers[typeid(TEvent)] = std::make_unique<HandlerList>();
    }
    auto subscriber = std::make_unique<EventCallback<TOwner, TEvent>>(
        ownerInstance, callbackFunction);
    subscribers[typeid(TEvent)]->push_back(std::move(subscriber));
  }
  
   /**
   * @brief Emits an event to all subscribers of the event's type.
   * 
   * @tparam TEvent The event type to emit.
   * @tparam TArgs Argument types to forward to the event constructor.
   * @param args Arguments forwarded to the event constructor.
   */
  template <typename TEvent, typename... TArgs>
  void EmitEvent(TArgs&&... args) {
    auto handlers = subscribers[typeid(TEvent)].get();
    if(handlers){
        for (auto it = handlers->begin(); it != handlers->end(); it++){
            auto handler = it->get();
            TEvent event (std::forward<TArgs>(args)...);
            handler->Execute(event);
        }
    }
  }
};
#endif