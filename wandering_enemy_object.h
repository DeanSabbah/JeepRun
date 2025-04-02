#ifndef KAMIKAZE_ENEMY_OBJECT_H_
#define KAMIKAZE_ENEMY_OBJECT_H_

#include "enemy_game_object.h"
#include "timer.h"

namespace game {
    class KamikazeEnemyObject : public EnemyGameObject {
    public:
        // Constructor
        KamikazeEnemyObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale, const float radius);
        // Destructor
        ~KamikazeEnemyObject();
        void Update(double delta_time) override;
        // Collision functions
        bool circleCollision(ColliderObject* other) const override;
        bool rayCollision(ColliderObject* other) const override;
    private:

        const float speed_ = 500.0f;
    };
}

#endif // ENEMY_GAME_OBJECT_H_