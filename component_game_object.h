#pragma once

#include "game_object.h"

namespace game {
	class ComponentGameObject : public GameObject {
	public:
		ComponentGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale, const float radius, const GameObject* parent) : GameObject(position, geom, shader, texture, scale), parent_(parent) {}
		virtual ~ComponentGameObject() = default;
		inline const GameObject* GetParent() const { return parent_; }
	protected:
		const GameObject* parent_;
	};
}