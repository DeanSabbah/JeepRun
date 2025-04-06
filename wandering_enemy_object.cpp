#include "wandering_enemy_object.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp> 

using namespace game;

WanderingEnemyObject::WanderingEnemyObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale, const float radius)
	: EnemyGameObject(position, geom, shader, texture, scale, radius) {
	t_.Start(3);
	dir = glm::normalize(glm::vec3(-1, 0, 0));
}

void WanderingEnemyObject::Update(double delta_time) {
	if (t_.Finished()) {
		dir = glm::normalize(glm::vec3(-1, 0, 0));
	}
}
