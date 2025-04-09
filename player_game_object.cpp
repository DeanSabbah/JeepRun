#include "player_game_object.h"
#include <iostream>

namespace game {

	/*
		PlayerGameObject inherits from GameObject
		It overrides GameObject's update method, so that you can check for input to change the velocity of the player
	*/

	PlayerGameObject::PlayerGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale, const float radius, GLFWwindow* window) : GameObject(position, geom, shader, texture, scale), ColliderObject(radius) {
		health = 15;
		invincibility_timer = new Timer();
		window_ = window;
		turret_component_ = new TurretComponent(position, geom, shader, 6, scale, radius, this);
		gun_component_ = new GunComponent(position, geom, shader, 7, scale, radius, turret_component_);
		components_.push_back(turret_component_);
		components_.push_back(gun_component_);
	}

	PlayerGameObject::~PlayerGameObject() {
		delete invincibility_timer;
		GameObject::~GameObject();
	}

	// Update function for moving the player object around
	void PlayerGameObject::Update(double delta_time) {
		if (!_dying) {
			// Apply friction to gradually reduce velocity
			if (velocity_ > 0.01f) { 
				velocity_ *= 0.98f;
			}
			else if (velocity_ < -0.01f) {
				velocity_ *= 0.98f;
			}
			else {
				velocity_ = 0.0f;
			}

			// Update position based on velocity and forward direction
			position_ += (float)delta_time * velocity_ * GetBearing();
		}

		if (invincibility_timer->Finished()) {
			invincible_ = false;
			setTexture(1);
		}

		for (int i = 0; i < components_.size(); i++) {
			components_[i]->Update(delta_time);
		}
		GameObject::Update(delta_time);
	}

	void PlayerGameObject::Render(glm::mat4 view_matrix, double current_time) {
		// Call the render function for all components
		for (int i = components_.size() - 1; i >= 0; i--) {
			components_[i]->Render(view_matrix, current_time);
		}
		GameObject::Render(view_matrix, current_time);
	}

	void PlayerGameObject::collect(const int type) {
		
		switch (type) {
			case 0:
				heal();
				break;
			case 1:
				gun_component_->addAmmo();
				break;
			case 2:
				invincibility_timer->Start(invincibility_time);
				invincible_ = true;
				break;
		}
		
	}

	bool PlayerGameObject::is_invincible() const {
		return invincible_;
	}
	// case 0 = forward, 1 = backwards, 2 = right, 3 = left
	void PlayerGameObject::update_velocity(int direction) {
		switch (direction) {
		case 0:// Forward
			if (velocity_ < max_velocity_)
				velocity_ += acceleration_;
			break;
		case 1:// Backward
			if (velocity_ > -max_velocity_ / 2.0f)
				velocity_ -= acceleration_;
			break;
		}
	}

	float PlayerGameObject::get_velocity() const {
		return velocity_;
	}

	void PlayerGameObject::set_velocity(float velocity) {
		velocity_ = velocity;
	}

	void PlayerGameObject::shoot_projectile() {
		// TODO: Implement shoot function
		dynamic_cast<GunComponent*>(components_[1])->shoot();
	}

	bool PlayerGameObject::circleCollision(ColliderObject* other) const {
		// Get the distance between the two objects
		float distance = glm::distance(GetPosition(), dynamic_cast<GameObject*>(other)->GetPosition());
		// If the distance is less than the sum of the radii, then the objects are colliding
		if (distance < radius_ + other->getRadius()) {
			return true;
		}
		return false;
	}

	bool PlayerGameObject::rayCollision(ColliderObject* other) const {
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

}
