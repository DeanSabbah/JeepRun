#pragma once

#include <vector>

#include "game_object.h"
#include "collider_object.h"
#include "weakling_game_object.h"

using namespace game;

class EndGoalObject : public GameObject, public ColliderObject {
	public:
		EndGoalObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale, float radius);

		void addWeakling(WeaklingObject* weakling) {
			 weaklings_.push_back(weakling);
		}
		void updateNumAlive() {
			num_allive_--;
		}
		void addAlive() {
			num_allive_++;
		}
		void setNumAlive(int count) {
			num_allive_ = count;
		}
		// 0 = game not over, 1 = win, 2 = lose
		int checkEndGoal() {
			if (num_allive_ == 0) {
				return 2;
			}
			else if (num_allive_ == weaklings_.size()) {
				return 1; // win
			}
			return 0; // game not over
		}
		bool circleCollision(ColliderObject* other) const override;
		bool rayCollision(ColliderObject* other) const override;
	private:
		std::vector<WeaklingObject*> weaklings_;
		int num_allive_ = -1;
};