#include "enemy_game_object.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp> 

using namespace game;

enum states_ {
	Patrol = 0,
	Intercept = 1
};

EnemyGameObject::EnemyGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale, const float radius) : GameObject(position, geom, shader, texture, scale), ColliderObject(radius) {
	// random height and width for the patrol area
	height_ = (rand() % 20 - 10) / 10.0f;
	radius_ = (rand() % 20 - 10) / 10.0f;
	// center is position -/+ height and width
	if (rand() % 2) {
		center_ = glm::vec3(position.x + radius_, position.y + height_, 0.0f);
	}
	else {
		center_ = glm::vec3(position.x - radius_, position.y - height_, 0.0f);
	}
}

EnemyGameObject::~EnemyGameObject() {
	GameObject::~GameObject();
}

void EnemyGameObject::Update(double delta_time) {
	// If the enemy is close enough to the player, it will intercept the player
	// Will not move the enemy if they are dying
	if (!_dying) {
		switch (state_) {
		case Intercept:
			intercept(delta_time);
			break;
		case Patrol:
			patrol(delta_time);
			break;
		}
	}

	// Update function for moving the enemy object around
	GameObject::Update(delta_time);
}

// Update the player position stored in the enemy object and calculate the distance between the player and the enemy
// If the distance is less than 2.0f, set the state to true, else set it to false
//@TODO: Make this virtual, overload in derived classes or make new function for setting state
void EnemyGameObject::updatePlayerPos(glm::vec3 player_pos) {
	player_pos_ = player_pos;
	distance_ = glm::distance(player_pos_, position_);
	determineState();
}

// Set the state of the enemy object
void EnemyGameObject::setState(int state) {
	state_ = state;
}

int EnemyGameObject::getState() const {
	return state_;
}

void EnemyGameObject::determineState() {
	// If the distance to the player is less than 2.0f, set the state to true, else set it to false
	if (distance_ < 2.0f)
		state_ = Intercept;
	else
		state_ = Patrol;
}

float EnemyGameObject::getSpeed() const {
	return speed_;
}

glm::vec3 EnemyGameObject::getVelocity() const {
	return velocity_;
}

glm::vec3 EnemyGameObject::getPLayerPos() const{
	return player_pos_;
}

void EnemyGameObject::patrol(double delta_time) {
	glm::vec3 new_pos;
	// Get the new position
	// Uses the current time to move the enemy in an elliptical motion
	new_pos.x = center_.x + radius_ * cos(glfwGetTime());
	new_pos.y = center_.y + height_ * sin(glfwGetTime());
	// Set rotation to forward
	SetRotation(atan2(new_pos.y - position_.y, new_pos.x - position_.x));
	// Set the new position
	SetPosition(new_pos);
}

void EnemyGameObject::intercept(double delta_time) {
	// Get the direction to the player
	velocity_= glm::normalize(player_pos_ - position_);
	// Set rotation to forward
	SetRotation(atan2(velocity_.y, velocity_.x));
	// Set the new position
	SetPosition(position_ + (velocity_ * 0.001f * (float)delta_time * speed_));
	// Update the distance to the player, so that when the enemy is far enough, it will patrol around it's current locaiton
	center_ = position_;
}

bool EnemyGameObject::circleCollision(ColliderObject* other) const {
	// Get the distance between the two objects
	float distance = glm::distance(GetPosition(), dynamic_cast<GameObject*>(other)->GetPosition());
	// If the distance is less than the sum of the radii, then the objects are colliding
	if (distance < radius_ + other->getRadius()) {
		return true;
	}
	return false;
}

bool EnemyGameObject::rayCollision(ColliderObject* other) const {
	GameObject *other_obj = dynamic_cast<GameObject*>(other);
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