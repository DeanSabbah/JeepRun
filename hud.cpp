#include "hud.h"
#include <glm/gtc/matrix_transform.hpp>

namespace game {

    HUD::HUD(Shader* shader, Geometry* geometry, GLuint texture)
        : shader_(shader), geometry_(geometry), texture_(texture), health_(100), ammo_(100) {
    }

    HUD::~HUD() {}

    void HUD::Update(double delta_time) {
		//health_ = player_->GetHealth();
		//ammo_ = player_->GetAmmo();
    }

    void HUD::Render(glm::mat4 view_matrix) {
        // Render health bar
        glm::mat4 health_transform = glm::translate(glm::mat4(1.0f), glm::vec3(-0.9f, 0.8f, 0.0f));
        health_transform = glm::scale(health_transform, glm::vec3(0.2f * health_ / 100.0f, 0.05f, 1.0f));
        shader_->SetUniformMat4("transform", view_matrix * health_transform);

        // Render ammo counter
        glm::mat4 ammo_transform = glm::translate(glm::mat4(1.0f), glm::vec3(-0.9f, 0.7f, 0.0f));
        ammo_transform = glm::scale(ammo_transform, glm::vec3(0.2f * ammo_ / 50.0f, 0.05f, 1.0f));
        shader_->SetUniformMat4("transform", view_matrix * ammo_transform);
    }

    void HUD::SetHealth(int health) {
        health_ = health;
    }

    void HUD::SetAmmo(int ammo) {
        ammo_ = ammo;
    }
} // namespace game
