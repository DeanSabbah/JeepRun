#include "enemy_projectile_object.h"
#include "gun_component_object.h"
#include <iostream>

namespace game {
	EnemyProjectileObject::EnemyProjectileObject(const glm::vec3& position, glm::vec3& bearing, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale, const float speed, const int damage, const float time, const float radius)
		: BulletProjectile(position, bearing, geom, shader, texture, scale, speed, damage, time, radius) {
	}
	
} // namespace game