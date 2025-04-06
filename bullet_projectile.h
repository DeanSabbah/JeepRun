#ifndef BULLET_PROJECTILE_H_
#define BULLET_PROJECTILE_H_

#include "projectile_game_object.h"
#include "timer.h"

namespace game {
    class BulletProjectile : public ProjectileGameObject {
    public:
        BulletProjectile(const glm::vec3& position, glm::vec3& bearing, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale, const float speed, const int damage, const float time, const float radius);
        ~BulletProjectile();
        void Update(double delta_time) override;

    };
}

#endif // BULLET_PROJECTILE_H_