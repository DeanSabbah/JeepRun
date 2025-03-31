#ifndef PLAYER_GAME_OBJECT_H_
#define PLAYER_GAME_OBJECT_H_

#include "game_object.h"
#include "timer.h"
#include "projectile_game_object.h"
#include "collider_object.h"

namespace game {

    // Inherits from GameObject
    class PlayerGameObject : public GameObject, public ColliderObject {

        public:
			// Constructor
            PlayerGameObject(const glm::vec3 &position, Geometry *geom, Shader *shader, GLuint texture, glm::vec2& scale, const float radius);
			// Destructor
            ~PlayerGameObject();

            void Update(double delta_time) override;
			// Function to collect objects
            void collect();
			// Returns if the player is invincible
			bool is_invincible() const;
			// Timer for invincibility
			Timer* invincibility_timer;
			// Update velocity
			// case 0 = forward, 1 = baclward, 2 = right, 3 = left
			void update_velocity(int direction);
			// Get the velocity of the player
			float get_velocity() const;
			// Set the velocity of the player
			void set_velocity(float velocity);
			// Shoots a projectile
			void shoot_projectile();
			// Returns cooldown status
			bool cooling_down() { return !cooldown->Finished(); }
			// Collision functions
			bool circleCollision(ColliderObject* other) const override;
			bool rayCollision(ColliderObject* other) const override;
			

        private:
			// Maximum velocity of the player
			const float max_velocity_ = 2.0f;
			// Acceleration of the player
			const float acceleration_ = 0.05f;
			// Velocity of the player
			glm::vec3 velocity_ = glm::vec3(0.0f, 0.0f, 0.0f);
			// Number of objects needed to collect to become invincible
			const int objs_needed = 10;
			// Number of objects collected
			int collected_objs = 0;
			// Amount of time the player is invincible
			const float invincibility_time = 10.0f;
			// Bool to check if the player is invincible
            bool invincible_= false;
			// Cooldown Timer
			Timer* cooldown;

    }; // class PlayerGameObject

} // namespace game

#endif // PLAYER_GAME_OBJECT_H_
