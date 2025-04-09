#include "hud.h"
#include <glm/gtc/matrix_transform.hpp>

#include "drawing_game_object.h"
#include "text_game_object.h"

namespace game {

    HUD::HUD(Shader* shader, Geometry* geometry, GLuint texture, PlayerGameObject * player)
        : shader_(shader), geometry_(geometry), texture_(texture), health_(100) {
        player_ = player;
    }

    HUD::~HUD() {}

    void HUD::Update(double delta_time) {
		health_ = player_->GetHealth();
        ammo_bullets_ = player_->GetAmmoBullets();
		ammo_rockets_ = player_->GetAmmoRockets();
        dynamic_cast<DrawingGameObject*>(hud_elms_[0])->SetHealth(health_);
		dynamic_cast<TextGameObject*>(hud_elms_[1])->SetAmmoCount(ammo_bullets_);
		dynamic_cast<TextGameObject*>(hud_elms_[2])->SetAmmoCount(ammo_rockets_);

		// Update the HUD elements
		for (GameObject* elm : hud_elms_) {
			elm->Update(delta_time);
		}
    }

    void HUD::Render(glm::mat4 view_matrix, double current_time) {
        for (GameObject* elm : hud_elms_) {
			elm->Render(view_matrix, current_time);
        }
    }

    void HUD::SetHealth(int health) {
        health_ = health;
    }
} // namespace game
