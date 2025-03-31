// Interface to make gameobjects collide with each other
#ifndef COLLIDER_OBJECT_H
#define COLLIDER_OBJECT_H

#include <glm/glm.hpp>

namespace game {
	class ColliderObject {
	public:
		// Constructor
		ColliderObject(float radius, bool type = 0) : radius_(radius), collider_type(type) {}
		virtual ~ColliderObject() = default;

		float getRadius() const { return radius_; }
		bool getColliderType() const { return collider_type; }
		// General collision function
		bool collide(ColliderObject* other) const { return collider_type ? circleCollision(other) : rayCollision(other); }
	protected:
		// Radius of the collider
		const float radius_;
		// Bool to determine type of collider object uses
		// false = circle, true = ray
		// Can change to enum later for more types
		const bool collider_type = false;

		virtual bool circleCollision(ColliderObject* other) const = 0;
		virtual bool rayCollision(ColliderObject* other) const = 0;
	};
}

#endif // COLLIDER_OBJECT_H