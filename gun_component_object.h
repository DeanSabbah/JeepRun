#pragma once

#include "component_game_object.h"
#include "timer.h"

namespace game {
	class GunComponent : public ComponentGameObject {
	public:
		GunComponent(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale, const float radius, GameObject* parent);
		virtual ~GunComponent() = default;
		// Init function
		void init();
		// Setters
		void setState(const int s);
		void addAmmo();

		//Getters
		inline int getState() const { return state_; }
		inline bool hasAmmo() const { return (state_ == 0) ? ammo_bullet_ > 0 : ammo_missile_ > 0; }

		// Gun functions
		void shoot();
		inline bool cooling_down() { return (state_ == 0) ? !cooldown_bullet->Finished() : !cooldown_missile->Finished(); }
	private:
		void Update(double delta_time) override;
		int state_ = 0; // 0 = machine gun, 1 = missile @TODO: add raygun if time allows
		// Initial fire rate
		float fire_rate_ = 0.2f;
		// Ammo counts
		int ammo_bullet_ = 100;
		int ammo_missile_ = 10;
		// Max ammo counts
		// Could add progression, larger ammo reserves
		const int max_bullet = 100;
		const int max_missile = 10;
		// Cooldown timers
		Timer* cooldown_bullet;
		Timer* cooldown_missile;
	};
}