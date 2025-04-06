#ifndef WANDERING_ENEMY_OBJECT_H_
#define WANDERING_ENEMY_OBJECT_H_

#include "enemy_game_object.h"
#include "timer.h"

namespace game {
    class WanderingEnemyObject : public EnemyGameObject {
    public:
        // Constructor
        WanderingEnemyObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale, const float radius);
        void Update(double delta_time) override;
        // Collision functions
        bool circleCollision(ColliderObject* other) const override;
        bool rayCollision(ColliderObject* other) const override;
    private:

        Timer t_;
        glm::vec3 dir;
        const float speed_ = 400.0f;
    };
}

#endif // ENEMY_GAME_OBJECT_H_