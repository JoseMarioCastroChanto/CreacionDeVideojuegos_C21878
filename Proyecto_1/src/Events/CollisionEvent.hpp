#ifndef COLLISIONEVENT_HPP
#define COLLISIONEVENT_HPP

#include "../ECS/ECS.hpp"
#include "../EventManager/Event.hpp"


/**
 * @brief Event triggered when two entities collide.
 */
class CollisionEvent : public Event {
 public:
 Entity a;///< First entity involved in the collision.
 Entity b;///< Second entity involved in the collision.

   /**
   * @brief Constructs a CollisionEvent with two entities.
   * @param a First entity involved.
   * @param b Second entity involved.
   */
 CollisionEvent(Entity a, Entity b) : a(a), b(b) {}
};
#endif