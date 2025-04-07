#ifndef RANGED_ENEMY_OBJECT_H_
#define RANGED_ENEMY_OBJECT_H_

#include "enemy_game_object.h"
#include "timer.h"

enum States_ {
	Follow = 0,
	Retreat = 1,
	Patrol = 2,
};

namespace game {
    class RangedEnemyObject : public EnemyGameObject {
    public:
        // Constructor
        RangedEnemyObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale, const float radius);
		~RangedEnemyObject() override;
        void Update(double delta_time) override;
        //void updatePlayerPos(glm::vec3 player_pos) override;

		// Determine the state of the enemy object
		void determineState() override;

        Timer* getShootTimer();
        
    private:
        Timer *t_;
        Timer *shoot_timer_;
        const float speed_ = 0.2f;
		const float range_ = 4.0f;
		const float follow_range_ = 6.0f;
		const float min_distance_ = 2.0f;

        // States
		//void intercept(double delta_time) override;
		//void patrol(double delta_time) override;
		void retreat(double delta_time);
    };
}

#endif // ENEMY_GAME_OBJECT_H_