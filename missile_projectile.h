#include "projectile_game_object.h"

using namespace game;

class MissileProjectile : public ProjectileGameObject {
public:
	MissileProjectile(const glm::vec3& position, glm::vec3& bearing, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale, const float speed, const int damage, const float time, const float radius);
	~MissileProjectile();
	void Update(double delta_time) override;
};