#ifndef HUD_H_
#define HUD_H_

#include <string>
#include <vector>
#include "shader.h"
#include "geometry.h"
#include "player_game_object.h"

namespace game {

    class HUD {
    public:
        HUD(Shader* shader, Geometry* geometry, GLuint texture, PlayerGameObject*);
        ~HUD();

        void Update(double delta_time);
        void Render(glm::mat4 view_matrix, double current_time);

        void SetHealth(int health);

		void addHudElement(GameObject* element) {
			hud_elms_.push_back(element);
		}

    private:
        Shader* shader_;
        Geometry* geometry_;
        GLuint texture_;

        int health_;
        int ammo_bullets_;
        int ammo_rockets_;

		PlayerGameObject* player_;

        std::vector<GameObject*> hud_elms_;
    };

} // namespace game

#endif // HUD_H_
