#include "kamikaze_enemy_object.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp> 
#include <random>

using namespace game;

enum States_ {
	Follow = 0,
	Explode = 1,
};

KamikazeEnemyObject::KamikazeEnemyObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale, const float radius)
	: EnemyGameObject(position, geom, shader, texture, scale, radius) {
	health = 3;
	speed_ = 1250.0f;
	state_ = Follow;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(-1, 1);
	//Generate a random number
	float num1 = distrib(gen);
	float num2 = distrib(gen);

	velocity_ = glm::normalize(glm::vec3(num1, num2, 0));
}

KamikazeEnemyObject::~KamikazeEnemyObject() {
	EnemyGameObject::~EnemyGameObject();
}

void KamikazeEnemyObject::Update(double delta_time) {
	if (!_dying && state_ == Follow) {
		intercept(delta_time);
	}
}

void KamikazeEnemyObject::determineState() {
	// If the distance to the player is less than 2.0f, set the state to true, else set it to false
	if (distance_ < min_distance_)
		state_ = Explode;
	else
		state_ = Follow;
}
bool KamikazeEnemyObject::getState() {
	if (state_ == Explode) {
		return true;
	}
	else if (state_ == Follow) {
		return false;
	}
}

void KamikazeEnemyObject::die() {
	_dying = true;
	timer->Start(0.01);
	setTexture(6);
}

