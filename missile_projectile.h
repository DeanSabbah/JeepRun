#ifndef MISSILE_PROJECTILE_H_
#define MISSILE_PROJECTILE_H_

#include "projectile_game_object.h"
#include "timer.h"

namespace game {
    class MissileProjectile : public ProjectileGameObject {
    public:
        MissileProjectile(const glm::vec3& position, glm::vec3& bearing, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale, const float speed, const int damage, const float time, const float radius, const bool type);
        ~MissileProjectile();
        void Update(double delta_time) override;
        // Collision functions
        bool circleCollision(ColliderObject* other) const override;
        bool rayCollision(ColliderObject* other) const override;

    };
}

#endif // MISSILE_PROJECTILE_H_