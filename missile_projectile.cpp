#include "missile_projectile.h"

using namespace game;

MissileProjectile::MissileProjectile(const glm::vec3& position, glm::vec3& bearing, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale, const float speed, const int damage, const float time, const float radius)
	: ProjectileGameObject(position, bearing, geom, shader, texture, scale, speed, damage, time, radius, true) {}

MissileProjectile::~MissileProjectile() {
	ProjectileGameObject::~ProjectileGameObject();
}

void MissileProjectile::Update(double delta_time) {
	ProjectileGameObject::Update(delta_time);
}