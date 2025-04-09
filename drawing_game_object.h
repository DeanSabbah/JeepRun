#ifndef DRAWING_GAME_OBJECT_H_
#define DRAWING_GAME_OBJECT_H_

#include "game_object.h"

namespace game {

    // Inherits from GameObject
    class DrawingGameObject : public GameObject {

        public:
            DrawingGameObject(const glm::vec3 &position, Geometry *geom, Shader *shader, GLuint texture, glm::vec2 offset);

			void SetHealth(float health) { health_ = health; }
            // Render function for the text
            void Render(glm::mat4 view_matrix, double current_time) override;
        private:
			const glm::vec2 offset_;
			float health_;
			float max_health_ = 15;


    }; // class DrawingGameObject

} // namespace game

#endif // DRAWING_GAME_OBJECT_H_
