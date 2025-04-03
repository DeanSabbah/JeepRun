#include "turret_component_object.h"
#include "player_game_object.h"
#include <iostream>

using namespace game;

TurretComponent::TurretComponent(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale, const float radius, GameObject* parent) : ComponentGameObject(position, geom, shader, texture, scale, radius, parent) {
	// Set the target direction to the parent's bearing
	target_dir_ = parent->GetBearing();
}

void TurretComponent::GetTargetDir() {
	double xpos, ypos;
	glfwGetCursorPos(dynamic_cast<PlayerGameObject*>(parent_)->get_window(), &xpos, &ypos);
	target_dir_ = glm::normalize(glm::vec3(xpos, ypos, 0.0f));
}

void TurretComponent::RotateTurret(double delta_time) {
	glm::vec3 curr_bearing = GetBearing();
	glm::vec3 curr_norm = glm::normalize(curr_bearing);
	// check if target_dir_ is not the same current bearing
	if (target_dir_ == curr_bearing) {
		return;
	}
	// Turn the turret towards the target direction at rotation_speed_
	// Calculate the rotation step
	float stepAngle = rotation_speed_ * delta_time;
	// Calculate the angle between the current direction and the target direction
	float angle = glm::acos(glm::dot(curr_norm, target_dir_));
	// Clamp the angle to the step angle
	if (angle > stepAngle) {
		angle = stepAngle;
	}
	// Calculate the rotation axis
	glm::vec3 rotationAxis = glm::cross(curr_norm, target_dir_);
	// Rotate the current direction towards the target direction
	glm::vec3 new_bearing = glm::rotate(curr_norm, angle, glm::normalize(rotationAxis));
	// Set the new rotation	
	SetRotation(atan2(new_bearing.y, new_bearing.x));
	// Update the position of the turret
	position_ = parent_->GetPosition();
}

void TurretComponent::Update(double delta_time) {
	std::cout << "Turret Pos: " << position_.x << ", " << position_.y << std::endl;
	GetTargetDir();
	RotateTurret(delta_time);

	GameObject::Update(delta_time);
}