#pragma once

#include "component_game_object.h"
#include "timer.h"

namespace game {
	class GunComponent : public ComponentGameObject {
	public:
		GunComponent(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale, const float radius, const GameObject* parent);
		virtual ~GunComponent() = default;
		// Init function
		void init();
		// Setters
		void setState(const int s);

		//Getters
		inline int getState() const { return state_; }

		// Gun functions
		inline void shoot() { cooldown_timer->Start(fire_rate_); };
	private:
		void Update(double delta_time) override;
		int state_ = 0; // 0 = machine gun, 1 = missile @TODO: add raygun if time allows
		float fire_rate_ = 0.2f;

		Timer* cooldown_timer;
	};
}