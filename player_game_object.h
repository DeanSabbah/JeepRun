#ifndef PLAYER_GAME_OBJECT_H_
#define PLAYER_GAME_OBJECT_H_

#include "game_object.h"
#include "timer.h"
#include "projectile_game_object.h"
#include "collider_object.h"
#include "component_game_object.h"
#include "collectible_game_object.h"
#include "turret_component_object.h"
#include "gun_component_object.h"

#include <vector>

namespace game {

    // Inherits from GameObject
    class PlayerGameObject : public GameObject, public ColliderObject {

        public:
			// Constructor
            PlayerGameObject(const glm::vec3 &position, Geometry *geom, Shader *shader, GLuint texture, glm::vec2& scale, const float radius, GLFWwindow* window);
			// Destructor
            ~PlayerGameObject();

            void Update(double delta_time) override;
			void Render(glm::mat4 view_matrix, double current_time) override;
			// Function to collect objects
            void collect(const int type);
			// Returns if the player is invincible
			bool is_invincible() const;
			// Timer for invincibility
			Timer* invincibility_timer;
			// Update velocity
			// case 0 = forward, 1 = baclward, 2 = right, 3 = left
			void update_velocity(int direction);
			// Get the velocity of the player
			float get_velocity() const;
			int GetHealth() const { return health; }
			int GetAmmo() const { return gun_component_->getAmmo(); }
			// Get the window
			inline GLFWwindow* get_window() const { return window_; }
			// Get component at index i
			inline ComponentGameObject* getComponent(int i) const { return components_[i]; }
			// Set the velocity of the player
			void set_velocity(float velocity);
			// Shoots a projectile
			void shoot_projectile();
			// Collision functions
			bool circleCollision(ColliderObject* other) const override;
			bool rayCollision(ColliderObject* other) const override;
			

        private:
			// Gun Component
			GunComponent* gun_component_;
			// Turret Component
			TurretComponent* turret_component_;
			// Maximum velocity of the player
			const float max_velocity_ = 2.0f;
			// Acceleration of the player
			const float acceleration_ = 0.05f;
			// Velocity of the player
			float velocity_ = 0.0f;
			// Number of objects needed to collect to become invincible
			const int objs_needed = 10;
			// Number of objects collected
			int collected_objs = 0;
			// Amount of time the player is invincible
			const float invincibility_time = 5.0f;
			// Components
			// 0 = turret, 1 = gun
			std::vector<ComponentGameObject*> components_;
			GLFWwindow* window_;

    }; // class PlayerGameObject

} // namespace game

#endif // PLAYER_GAME_OBJECT_H_
