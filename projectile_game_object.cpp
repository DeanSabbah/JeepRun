#include "projectile_game_object.h"
#include <iostream>

namespace game {
	ProjectileGameObject::ProjectileGameObject(const glm::vec3& position, glm::vec3& bearing, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale, const float speed, const int damage, const float time, const float radius, const bool type) : GameObject(position, geom, shader, texture, scale), ColliderObject(radius, type), speed_(speed), damage_(damage) {
		timer = new Timer();
		timer->Start(time);
		SetRotation(glm::atan(bearing.y, bearing.x));
		setTexture(texture);
	}
	ProjectileGameObject::~ProjectileGameObject() {
		delete timer;
		GameObject::~GameObject();
	}
	void ProjectileGameObject::Update(double delta_time) {
		SetPosition(GetPosition() + speed_ * GetBearing() * (float)delta_time);
		GameObject::Update(delta_time);
	}
	bool ProjectileGameObject::circleCollision(ColliderObject* other) const {
		// Get the distance between the two objects
		float distance = glm::distance(GetPosition(), dynamic_cast<GameObject*>(other)->GetPosition());
		// If the distance is less than the sum of the radii, then the objects are colliding
		if (distance < radius_ + other->getRadius()) {
			return true;
		}
		return false;
	}

	bool ProjectileGameObject::rayCollision(ColliderObject* other) const {
		// Ray origin and direction
		glm::vec3 rayOrigin = GetPosition();
		glm::vec3 rayDirection = glm::normalize(GetBearing());

		// Circle center and radius
		glm::vec3 circleCenter = dynamic_cast<GameObject*>(other)->GetPosition();
		float circleRadius = other->getRadius();

		// Vector from ray origin to circle center
		glm::vec3 oc = circleCenter - rayOrigin;

		// Project oc onto the ray direction
		float t = glm::dot(2.0f * oc, rayDirection);

		// Closest point on the ray to the circle center
		glm::vec3 closestPoint = rayOrigin + t * rayDirection;

		// Distance from the closest point to the circle center
		float distance = glm::length(closestPoint - circleCenter);

		// Check if the distance is less than the circle's radius
		bool intersect = distance <= circleRadius;

		// Check if the closest point is within the max distance from the ray origin
		float distanceFromOrigin = glm::length(closestPoint - rayOrigin);
		return intersect && distanceFromOrigin <= (radius_ + circleRadius);
	}
} // namespace game