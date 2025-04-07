#ifndef RANGED_ENEMY_OBJECT_H_
#define RANGED_ENEMY_OBJECT_H_

#include "enemy_game_object.h"
#include "timer.h"

namespace game {
    class RangedEnemyObject : public EnemyGameObject {
    public:
        // Constructor
        RangedEnemyObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale, const float radius);
        void Update(double delta_time) override;
        void updatePlayerPos(glm::vec3 player_pos) override;
        Timer* getShootTimer();
        
    private:

        Timer *t_;
        Timer *shoot_timer_;
        const float speed_ = 0.2f;
    };
}

#endif // ENEMY_GAME_OBJECT_H_