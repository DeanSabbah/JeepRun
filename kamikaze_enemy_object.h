#ifndef KAMIKAZE_ENEMY_OBJECT_H_
#define KAMIKAZE_ENEMY_OBJECT_H_

#include "enemy_game_object.h"
#include "timer.h"

namespace game {
    class KamikazeEnemyObject : public EnemyGameObject {
    public:
        // Constructor
        KamikazeEnemyObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale, const float radius);
        ~KamikazeEnemyObject() override;
        void Update(double delta_time) override;
        void determineState() override;
        bool getState();
		bool inRange(glm::vec3 pos) { 
            bool dist = glm::distance(pos, position_) <= min_distance_;
			if (dist) {
				state_ = 1;
			}
			return dist;
        }
        void die() override;

    private:
        const float min_distance_ = 1.0f;
    };
}

#endif // ENEMY_GAME_OBJECT_H_