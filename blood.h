#pragma once

#include <glm/glm.hpp>

#include "game_object.h"

using namespace game;

class Blood : public GameObject {
	public:
		Blood(glm::vec3& posiiton, Geometry* geom, Shader* shader) : GameObject(posiiton, geom, shader, 12, glm::vec2(1.0f)) {
			_dying = true;
			timer->Start(1.0f);
		}
};