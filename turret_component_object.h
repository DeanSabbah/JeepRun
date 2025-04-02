#pragma once

#include "component_game_object.h"

#include <glm/glm.hpp>

namespace game {
	class TurretComponent : public ComponentGameObject {
	public:
		TurretComponent(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale, const float radius, const GameObject* parent);
		virtual ~TurretComponent() = default;
	private:
		void Update(double delta_time) override;
		float rotation_speed_ = 0.01f;
		glm::vec3 target_dir_;
	};
}