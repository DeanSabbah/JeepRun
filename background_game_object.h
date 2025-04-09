#ifndef BACKGROUND_GAME_OBJECT_H_
#define BACKGROUND_GAME_OBJECT_H_

#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/rotate_vector.hpp> 
#define GLEW_STATIC
#include <GL/glew.h>

#include "game_object.h"
namespace game {

	class BackgroundGameObject : public GameObject {
	public:
		BackgroundGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale);
		void Render(glm::mat4 view_matrix, double current_time) override;

	private:

	};
}

#endif

