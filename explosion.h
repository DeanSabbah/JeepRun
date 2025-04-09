#pragma once

#include "game_object.h"

#include <unordered_set>

using namespace game;

class Explosion : public GameObject {
public:
	Explosion(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale, const float damage, const float radius)
		: GameObject(position, geom, shader, texture, scale), damage_(damage), radius_(radius) {
		SetRotation(0.0f);
		_dying = true;
	}
	~Explosion() {
		GameObject::~GameObject();
	}
	inline float GetDamage() const { return damage_; }
	inline float GetRadius() const { return radius_; }
	float GetDamageAt(const float distance) const;
	inline bool IsDamaged(GameObject* object) const { return affected_objects_.find(object) != affected_objects_.end(); }
	inline void AddAffectedObject(GameObject* object) { affected_objects_.insert(object); }
private:
	const float damage_;
	const float radius_;
	// Set to keep track of objects that have been affected by the explosion
	std::unordered_set<GameObject*> affected_objects_;
};