#include "weakling_game_object.h"

#include <iostream>

using namespace game;

WeaklingObject::WeaklingObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale, float radius, glm::vec3 goal)
	: GameObject(position, geom, shader, texture, scale), ColliderObject(radius) {
	goal_ = goal;
	health = 3;
}

void WeaklingObject::Update(double delta_time) {
	if (!_dying && !reached_end_) {
		moveTowardsGoal(delta_time);
	}
	GameObject::Update(delta_time);
}

void WeaklingObject::moveTowardsGoal(double delta_time) {
	glm::vec3 direction = glm::normalize(goal_ - position_);
	position_ += (float)delta_time * speed_ * direction;
}

bool WeaklingObject::circleCollision(ColliderObject* other) const {
	// Get the distance between the two objects
	float distance = glm::distance(GetPosition(), dynamic_cast<GameObject*>(other)->GetPosition());
	// If the distance is less than the sum of the radii, then the objects are colliding
	if (distance < radius_ + other->getRadius()) {
		return true;
	}
	return false;
}

bool WeaklingObject::rayCollision(ColliderObject* other) const {
	GameObject* other_obj = dynamic_cast<GameObject*>(other);
	// Ray origin and direction
	glm::vec3 rayOrigin = GetPosition();
	glm::vec3 rayDirection = glm::normalize(GetBearing());

	// Circle center and radius
	glm::vec3 circleCenter = other_obj->GetPosition();
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