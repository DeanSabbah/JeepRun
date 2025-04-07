#ifndef ENEMY_PROJECTILE_OBJECT_H_
#define ENEMY_PROJECTILE_OBJECT_H_

#include "bullet_projectile.h"

namespace game {
	class EnemyProjectileObject : public BulletProjectile {
	public:
		EnemyProjectileObject(const glm::vec3& position, glm::vec3& bearing, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale, const float speed, const int damage, const float time, const float radius);

	};
}

#endif // PROJECTILE_GAME_OBJECT_H_