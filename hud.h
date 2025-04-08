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
        HUD(Shader* shader, Geometry* geometry, GLuint texture);
        ~HUD();

        void Update(double delta_time);
        void Render(glm::mat4 view_matrix);

        void SetHealth(int health);
        void SetAmmo(int ammo);

    private:
        Shader* shader_;
        Geometry* geometry_;
        GLuint texture_;

        int health_;
        int ammo_;

		PlayerGameObject* player_;
    };

} // namespace game

#endif // HUD_H_
