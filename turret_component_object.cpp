#include "turret_component_object.h"

using namespace game;

TurretComponent::TurretComponent(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale, const float radius, const GameObject* parent) : ComponentGameObject(position, geom, shader, texture, scale, radius, parent) {
	// Set the target direction to the parent's bearing
	target_dir_ = parent->GetBearing();
}

void TurretComponent::Update(double delta_time) {
	// check if target_dir_ is not the same current bearing
	if (target_dir_ == GetBearing()) {
		GameObject::Update(delta_time);
		return;
	}
	// Turn the turret towards the target direction at rotation_speed_
	//TODO: Finish this
}