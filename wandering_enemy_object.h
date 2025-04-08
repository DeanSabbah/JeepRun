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
    private:

        Timer* t_;
    };
}

#endif // ENEMY_GAME_OBJECT_H_