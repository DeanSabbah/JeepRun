#include "gun_component_object.h"

using namespace game;

GunComponent::GunComponent(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale, const float radius, GameObject* parent) : ComponentGameObject(position, geom, shader, texture, scale, radius, parent) {
	cooldown_timer = new Timer();
}

void GunComponent::init() {
	position_ = parent_->GetPosition();
	SetRotation(parent_->GetRotation());
}

void GunComponent::setState(const int s) {
	state_ = s;
	switch (state_) {
		case 0:
			fire_rate_ = 0.2f;
			setTexture(10);
			break;
		case 1:
			setTexture(11);
			fire_rate_ = 1.2f;
			break;
	}
}

void GunComponent::Update(double delta_time) {
	position_ = parent_->GetPosition();
	SetRotation(parent_->GetRotation());
	GameObject::Update(delta_time);
}