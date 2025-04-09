#include "gun_component_object.h"

#include <iostream>

using namespace game;

GunComponent::GunComponent(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale, const float radius, GameObject* parent) : ComponentGameObject(position, geom, shader, texture, scale, radius, parent) {
	cooldown_bullet = new Timer();
	cooldown_missile = new Timer();
}

void GunComponent::init() {
	position_ = parent_->GetPosition();
	SetRotation(parent_->GetRotation());
	position_ += GetBearing() * 0.45f;
}

void GunComponent::setState(const int s) {
	state_ = s;
	switch (state_) {
		case 0:
			fire_rate_ = 0.2f;
			setTexture(18);
			break;
		case 1:
			setTexture(19);
			fire_rate_ = 1.2f;
			break;
	}
}

void GunComponent::addAmmo() {
	ammo_bullet_ += 25;
	if (ammo_bullet_ > max_bullet) {
		ammo_bullet_ = max_bullet;
	}
	ammo_missile_ += 5;
	if (ammo_missile_ > max_missile) {
		ammo_missile_ = max_missile;
	}
}

void GunComponent::shoot(){
	switch (state_) {
		case 0:
			if (ammo_bullet_ > 0) {
				ammo_bullet_--;
				cooldown_bullet->Start(fire_rate_);
				std::cout << "Num Bullets left: " << ammo_bullet_ << std::endl;
			}
			break;
		case 1:
			if (ammo_missile_ > 0) {
				ammo_missile_--;
				cooldown_missile->Start(fire_rate_);
				std::cout << "Num Missiles left: " << ammo_missile_ << std::endl;
			}
			break;
	}
}

void GunComponent::Update(double delta_time) {
	position_ = parent_->GetPosition();
	SetRotation(parent_->GetRotation());
	position_ += GetBearing() * 0.45f;
	GameObject::Update(delta_time);
}