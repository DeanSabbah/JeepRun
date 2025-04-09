#pragma once

#include "game_object.h"
#include "collider_object.h"

using namespace game;

class WeaklingObject : public GameObject, public ColliderObject {
	public:
		WeaklingObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale, float radius, glm::vec3 goal);
		void Update(double delta_time) override;

		void reachEnd() {
			reached_end_ = true;
		}

		void setGoal(glm::vec3 goal) {
			goal_ = goal;
		}

		bool circleCollision(ColliderObject* other) const override;
		bool rayCollision(ColliderObject* other) const override;
	private:
		void moveTowardsGoal(double delta_time);

		glm::vec3 goal_;
		float speed_ = 1.0f;

		bool reached_end_ = false;
};