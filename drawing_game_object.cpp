#include <glm/gtc/matrix_transform.hpp>

#include "drawing_game_object.h"

#include <iostream>

namespace game {

DrawingGameObject::DrawingGameObject(const glm::vec3 &position, Geometry *geom, Shader *shader, GLuint texture, glm::vec2 offset) : GameObject(position, geom, shader, texture, glm::vec2(1.0f)), offset_(offset) { }


void DrawingGameObject::Render(glm::mat4 view_matrix, double current_time) {

    // Set up the shader
    shader_->Enable();

    // Set up the view matrix
    shader_->SetUniformMat4("view_matrix", view_matrix);

    shader_->SetUniform1f("health", health_);

    shader_->SetUniform1f("maxHealth", max_health_);

    // Setup the scaling matrix for the shader
    glm::mat4 scaling_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale_.x, scale_.y, 1.0));

    // Setup the rotation matrix for the shader
    glm::mat4 rotation_matrix = glm::rotate(glm::mat4(1.0f), angle_, glm::vec3(0.0, 0.0, 1.0));

    // Set up the translation matrix for the shader
    glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-0.3f, -1.2f, 0.0f));

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
}

} // namespace game
