#include "background_game_object.h"

namespace game {
	BackgroundGameObject::BackgroundGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, glm::vec2& scale)
		: GameObject(position, geom, shader, texture, scale) {
	}

	void BackgroundGameObject::Render(glm::mat4 view_matrix, double current_time) {
		for (int i = -4;i < 5;i++) {
			for (int j = -4;j < 5;j++) {
                // Set up the shader
                shader_->Enable();

                // Set the grayscale mode
                shader_->SetUniform1i("grayscale", ghost_);

                // Set the invincibility mode
                shader_->SetUniform1i("invincible", invincible_);

                // Set up the view matrix
                shader_->SetUniformMat4("view_matrix", view_matrix);

                // Setup the scaling matrix for the shader
                glm::mat4 scaling_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale_.x, scale_.y, 1.0));

                // Setup the rotation matrix for the shader
                glm::mat4 rotation_matrix = glm::rotate(glm::mat4(1.0f), angle_, glm::vec3(0.0, 0.0, 1.0));

                // Set up the translation matrix for the shader
                glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(position_.x * i, position_.y * j, position_.z));

                // Setup the transformation matrix for the shader
                glm::mat4 transformation_matrix = translation_matrix * rotation_matrix * scaling_matrix;

                // Set the transformation matrix in the shader
                shader_->SetUniformMat4("transformation_matrix", transformation_matrix);

                // Set up the geometry
                geometry_->SetGeometry(shader_->GetShaderProgram());

                // Bind the entity's texture
                glBindTexture(GL_TEXTURE_2D, texture_);

                // Draw the entity
                glDrawElements(GL_TRIANGLES, geometry_->GetSize(), GL_UNSIGNED_INT, 0);

                shader_->Disable();
			}

		}
	}
}



