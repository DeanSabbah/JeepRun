#ifndef ENEMY_GAME_OBJECT_H_
#define ENEMY_GAME_OBJECT_H_

#include "game_object.h"
#include "timer.h"
#include "collider_object.h"

namespace game {
	class EnemyGameObject : public GameObject, public ColliderObject {
		public:
			// Constructor
			EnemyGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale, const float radius);
			// Destructor
			~EnemyGameObject();
			void Update(double delta_time) override;
			void updatePlayerPos(glm::vec3 player_pos);
			void setState(bool state);
			bool getState() const;
			float getSpeed() const;
			// Collision functions
			bool circleCollision(ColliderObject* other) const override;
			bool rayCollision(ColliderObject* other) const override;
		private:
			// Object's velcity
			glm::vec3 velocity_;
			// Object's speed
			const float speed_ = 420.0f;
			// Enemy states
			void patrol(double delta_time);
			void intercept(double delta_time);
			// Player position
			glm::vec3 player_pos_;
			// Distance from player
			float distance_ = NULL;
			// Boolean switch for movement state
			// Can change to int later for more states
			bool state_ = false;
			// Center to patrol
			glm::vec3 center_;
			// Patrol height
			float height_ = NULL;
			// Patrol radius
			float radius_ = NULL;

			Timer* move_timer;
	};
}

#endif // ENEMY_GAME_OBJECT_H_