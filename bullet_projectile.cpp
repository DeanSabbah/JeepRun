#include "bullet_projectile.h"
#include <iostream>

namespace game {
    BulletProjectile::BulletProjectile(const glm::vec3& position, glm::vec3& bearing, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale, const float speed, const int damage, const float time, const float radius) : ProjectileGameObject(position, bearing, geom, shader, texture, scale, speed, damage, time, radius, false) {}
    BulletProjectile::~BulletProjectile() {
        ProjectileGameObject::~ProjectileGameObject();
    }
    void BulletProjectile::Update(double delta_time) {
		ProjectileGameObject::Update(delta_time);
    }
} // namespace game