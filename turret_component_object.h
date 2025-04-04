#pragma once

#include "component_game_object.h"

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>


namespace game {
	class TurretComponent : public ComponentGameObject {
	public:
		TurretComponent(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale, const float radius, GameObject* parent);
		virtual ~TurretComponent() = default;
	private:
		void GetTargetDir();
		void RotateTurret(double delta_time);

		void Update(double delta_time) override;
		float rotation_speed_ = 2.0f;
		glm::vec3 target_dir_;
	};
}