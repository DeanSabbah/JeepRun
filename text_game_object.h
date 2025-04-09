#ifndef TEXT_GAME_OBJECT_H_
#define TEXT_GAME_OBJECT_H_

#include <string>

#include "game_object.h"

namespace game {

    // Inherits from GameObject
    class TextGameObject : public GameObject {

        public:
            TextGameObject(const glm::vec3 &position, Geometry *geom, Shader *shader, GLuint texture);

            // Text to be displayed
            std::string GetText(void) const;
            void SetText(std::string text);
			// Set the ammo count
			void SetAmmoCount(int ammo_count) { ammo_count_ = ammo_count; }
			void SetPos(glm::vec3 pos) { pos_ = pos; }

            // Render function for the text
            void Render(glm::mat4 view_matrix, double current_time) override;

        private:
            std::string text_;
            int ammo_count_;

			glm::vec3 pos_;

    }; // class TextGameObject

} // namespace game

#endif // TEXT_GAME_OBJECT_H_
