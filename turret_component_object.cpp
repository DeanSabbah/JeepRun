#include "turret_component_object.h"
#include "player_game_object.h"
#include <iostream>

using namespace game;

TurretComponent::TurretComponent(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale, const float radius, GameObject* parent) : ComponentGameObject(position, geom, shader, texture, scale, radius, parent) {
	// Set the target direction to the parent's bearing
	target_dir_ = parent->GetBearing();
}

void TurretComponent::GetTargetDir() {
	// Get the mouse position in screen coordinates
	double x, y;
	glfwGetCursorPos(dynamic_cast<PlayerGameObject*>(parent_)->get_window(), &x, &y);
	// Get the window size
	int width, height;
	glfwGetWindowSize(dynamic_cast<PlayerGameObject*>(parent_)->get_window(), &width, &height);

	// Convert the mouse position to normalized device coordinates (NDC)
	glm::vec3 mouse_ndc = glm::vec3((x / width) * 2.0f - 1.0f, 1.0f - (y / height) * 2.0f, 0.0f);

	// Get the turret's position
	glm::vec3 turret_pos = GetPosition();
	glm::vec3 mouse_world = glm::vec3(mouse_ndc.x * width / 2.0f, mouse_ndc.y * height / 2.0f, 0.0f);

	// Get the direction from the turret to the mouse position
	glm::vec3 dir = glm::normalize(mouse_world - turret_pos);

	// Set the target direction to the direction from the turret to the mouse position
	target_dir_ = dir;
}

void TurretComponent::RotateTurret(double delta_time) {
	glm::vec3 curr_bearing = GetBearing();
	glm::vec3 curr_norm = glm::normalize(curr_bearing);
	// check if target_dir_ is not the same current bearing
	if (glm::length(target_dir_ - curr_norm) < 0.001f) {
		return;
	}
	// Calculate the rotation step
	float stepAngle = rotation_speed_ * delta_time;
	// Calculate the angle between the current direction and the target direction
	float dotProduct = glm::dot(curr_norm, target_dir_);
	dotProduct = glm::clamp(dotProduct, -1.0f, 1.0f);
	float angle = glm::acos(dotProduct);
	// Clamp the angle to the step angle
	if (angle > stepAngle) {
		angle = stepAngle;
	}
	// Calculate the rotation axis
	glm::vec3 rotationAxis = glm::cross(curr_norm, target_dir_);
	if (glm::length(rotationAxis) < 0.001f) {
		if (dotProduct < 0.0f) {
			rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
		}
		else {
			return;
		}
	}

	// Rotate the current direction towards the target direction
	glm::vec3 new_bearing = glm::rotate(curr_norm, angle, glm::normalize(rotationAxis));
	new_bearing = glm::normalize(new_bearing);

	// Set the new rotation
	SetRotation(atan2(new_bearing.y, new_bearing.x));
}

void TurretComponent::Update(double delta_time) {
	GetTargetDir();
	RotateTurret(delta_time);
	// Update the position of the turret
	position_ = parent_->GetPosition();

	GameObject::Update(delta_time);
}