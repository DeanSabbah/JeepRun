#include "ranged_enemy_object.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp> 
#include <random>

using namespace game;

RangedEnemyObject::RangedEnemyObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale, const float radius)
	: EnemyGameObject(position, geom, shader, texture, scale, radius) {
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

void RangedEnemyObject::Update(double delta_time) {
	std::cout << getState() << std::endl;
	if (!getState()) {
		if (t_->Finished()) {
			// Random point in angle opening
			float r_num = ((float)rand()) / ((float)RAND_MAX);
			float opening = 360 * 3.141592 / 180.0; // Add PI from the glm library
			float r_angle = r_num * 2.0 * opening + angle_ - opening;
			float r = 10.0f;
			glm::vec3 target(r * cos(r_angle), r * sin(r_angle), 0.0);
			// Steering to target
			glm::vec3 desired = target;
			glm::vec3 steering = desired + velocity_;
			steering /= glm::length(steering);
			steering *= 0.1; // Adjust force magnitude
			velocity_ += steering;
			// Reset timer to only update wander every 3s
			t_->Start(3);
			//std::cout << velocity_[0] << ", " << velocity_[1] << std::endl;
			//std::cout << position_[0] << ", " << position_[1] << std::endl;
		}

		position_ += velocity_ * float(delta_time) * speed_;
	}

	if (getState()) {
		if (shoot_timer_->Finished()) {
			std::cout << "finished" << std::endl;
			shoot_timer_->Start(2);
		}
		intercept(delta_time);
	}
}

void RangedEnemyObject::updatePlayerPos(glm::vec3 player_pos) {
	player_pos_ = player_pos;
	distance_ = glm::distance(player_pos_, position_);
	if (!getState() && distance_ < 5.0f)
		shoot_timer_ = new Timer();
		setState(true);
		shoot_timer_->Start(2);
}

Timer* RangedEnemyObject::getShootTimer() {
	return shoot_timer_;
}
