#include "ranged_enemy_object.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp> 
#include <random>

using namespace game;

RangedEnemyObject::RangedEnemyObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale, const float radius)
	: EnemyGameObject(position, geom, shader, texture, scale, radius) {
	health = 3;
	shoot_timer_ = new Timer();
	t_ = new Timer();
	t_->Start(3);
	state_ = false;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(-1, 1);
	//Generate a random number
	float num1 = distrib(gen);
	float num2 = distrib(gen);

	velocity_ = glm::normalize(glm::vec3(num1, num2, 0));
}

RangedEnemyObject::~RangedEnemyObject() {
	delete t_;
	delete shoot_timer_;
	EnemyGameObject::~EnemyGameObject();
}

void RangedEnemyObject::Update(double delta_time) {
	if (!_dying) {
		switch (getState()) {
		case Follow:
			intercept(delta_time);
			break;
		case Retreat:
			retreat(delta_time);
			break;
		case Patrol:
			patrol(delta_time);
			break;
			//	if (t_->Finished()) {
			//		// Random point in angle opening
			//		float r_num = ((float)rand()) / ((float)RAND_MAX);
			//		float opening = 360 * 3.141592 / 180.0; // Add PI from the glm library
			//		float r_angle = r_num * 2.0 * opening + angle_ - opening;
			//		float r = 10.0f;
			//		glm::vec3 target(r * cos(r_angle), r * sin(r_angle), 0.0);
			//		// Steering to target
			//		glm::vec3 desired = target;
			//		glm::vec3 steering = desired + velocity_;
			//		steering /= glm::length(steering);
			//		steering *= 0.1; // Adjust force magnitude
			//		velocity_ += steering;
			//		// Reset timer to only update wander every 3s
			//		t_->Start(3);
			//		//std::cout << velocity_[0] << ", " << velocity_[1] << std::endl;
			//		//std::cout << position_[0] << ", " << position_[1] << std::endl;
			//	}

			//	position_ += velocity_ * float(delta_time) * speed_;
			//}

			//if (getState()) {
			//	if (shoot_timer_->Finished()) {
			//		std::cout << "finished" << std::endl;
			//		shoot_timer_->Start(2);
			//	}
			//	intercept(delta_time);
			//}
		}
	}
}

//void RangedEnemyObject::updatePlayerPos(glm::vec3 player_pos) {
//	player_pos_ = player_pos;
//	distance_ = glm::distance(player_pos_, position_);
//	if (!getState() && distance_ < 5.0f)
//		shoot_timer_ = new Timer();
//		setState(true);
//		shoot_timer_->Start(2);
//}

void RangedEnemyObject::determineState() {
	// If the distance to the player is less than 2.0f, set the state to true, else set it to false
	if (follow_range_ >= distance_ && distance_ >= min_distance_)
		state_ = Follow;
	else if (distance_ < min_distance_)
		state_ = Retreat;
	else
		state_ = Patrol;
}

Timer* RangedEnemyObject::getShootTimer() {
	return shoot_timer_;
}

void RangedEnemyObject::retreat(double delta_time) {
	// Moves away from the player
	// Finds the angle to the player
	float angle = atan2(player_pos_.y - position_.y, player_pos_.x - position_.x);
	// Sets the angle to the opposite direction
	angle += glm::pi<float>();
	// Find the new velocity
	velocity_ = glm::vec3(cos(angle), sin(angle), 0);
	// Set the new position
	SetPosition(position_ + (velocity_ * 0.001f * (float)delta_time * speed_));
}