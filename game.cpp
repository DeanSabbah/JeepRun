#include <stdexcept>
#include <string>
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp> 
#include <SOIL/SOIL.h>
#include <iostream>

#include <path_config.h>

#include "sprite.h"
#include "shader.h"
#include "player_game_object.h"
#include "background_game_object.h"
#include "collectible_game_object.h"
#include "enemy_game_object.h"
#include "wandering_enemy_object.h"
#include "ranged_enemy_object.h"
#include "kamikaze_enemy_object.h"
#include "bullet_projectile.h"
#include "missile_projectile.h"
#include "enemy_projectile_object.h"
#include "game.h"
#include "particles.h"
#include "blood_particles.h"
#include "particle_system.h"
#include "explosion.h"
#include "blood.h"
#include "drawing_game_object.h"
#include "text_game_object.h"
#include "end_goal_object.h"
#include "weakling_game_object.h"

namespace game {

// Some configuration constants
// They are written here as global variables, but ideally they should be loaded from a configuration file

// Globals that define the OpenGL window and viewport
const char *window_title_g = "Game Demo";
const unsigned int window_width_g = 800;
const unsigned int window_height_g = 600;
const glm::vec3 viewport_background_color_g(0.0, 0.0, 1.0);
// Const to keep track of the number of background and hud objects
const int BACKGROUND_OBJECTS = 2;

// Directory with game resources such as textures
const std::string resources_directory_g = RESOURCES_DIRECTORY;


void Game::SetupGameWorld(void)
{
    srand(time(NULL));

    // Setup the game world

    // **** Load all the textures that we will need
    //
    // Declare all the textures here
    std::vector<std::string> textures;
    enum { tex_red_ship = 0,
           kamekaze = 1,
           ranged= 2,
           tex_stars = 3,
           tex_orb = 4,
           explosion = 5,
           invincible = 6,
           fireball = 7,
           bullet = 8,
           missile = 9,
           nothing = 10,
           square = 11,
           health = 12,
           bullet_ammo = 13,
           yellow_orb = 14,
           text = 15,
           wanderer = 16,
           barrel = 17,
           rocket = 18,
		   boat = 19,
           weakling = 20};
    textures.push_back("/textures/jeep_trailcat.png"); 
    textures.push_back("/textures/ZombieToast.png"); 
    textures.push_back("/textures/gun.png");
    textures.push_back("/textures/desert.png");
    textures.push_back("/textures/orb.png");
    textures.push_back("/textures/Explosion.png");
	textures.push_back("/textures/turret_01_mk1.png");
	textures.push_back("/textures/FireBall.png");
	textures.push_back("/textures/bullet.png");
	textures.push_back("/textures/roc.png");
	textures.push_back("/textures/nothing.png");
	textures.push_back("/textures/square.png");
    textures.push_back("/textures/health-red 32px.png");
    textures.push_back("/textures/ammo-rifle 32px.png");
    textures.push_back("/textures/invincibility.png");
    textures.push_back("/textures/font.png");
    textures.push_back("/textures/idle.png");
    textures.push_back("/textures/barrel_01_mk1.png");
    textures.push_back("/textures/rocket_01_mk1.png");
    textures.push_back("/textures/boat.png");
	textures.push_back("/textures/weakling.png");
    // Load textures
    LoadTextures(textures);


    // **** Setup all the game objects in the world

    // Setup the player object (position, texture, vertex count)
    // Note that, in this specific implementation, the player object should always be the first object in the game object vector 
    game_objects_.push_back(new PlayerGameObject(glm::vec3(0.0f, 0.0f, 0.0f), sprite_, &sprite_shader_, tex_[tex_red_ship], glm::vec2(1.5f, 1.0f), 0.4f, window_));
    float pi_over_two = glm::pi<float>() / 2.0f;
    game_objects_[0]->SetRotation(pi_over_two);

    // Setup other objects
    game_objects_.push_back(new KamikazeEnemyObject(glm::vec3(-5.0f, 5.0f, 0.0f), sprite_, &sprite_shader_, tex_[1], glm::vec2(1.0f), 0.4f));
    game_objects_[1]->SetRotation(pi_over_two);
    game_objects_.push_back(new KamikazeEnemyObject(glm::vec3(5.0f, -4.5f, 0.0f), sprite_, &sprite_shader_, tex_[1], glm::vec2(1.0f), 0.4f));
    game_objects_[2]->SetRotation(pi_over_two);
	// Setup collectible objects in random locations
	for (int i = 0; i < 90; i++) {
        // Generate number from 0 to 9
		int type = rand() % 10;
		if (type == 0) {
			type = 0;
		}
        else if (type >= 1 && type <= 5) {
			type = 1;
        }
        else {
			type = 2;
        }

		float x = (rand() % 34) - 17;
		float y = (rand() % 34) - 17;
		game_objects_.push_back(new CollectibleGameObject(glm::vec3(x, y, 0.0f), sprite_, &sprite_shader_, tex_[type + 12], glm::vec2(1.0f, 1.0f), type, 0.3f));
		game_objects_[3 + i]->SetRotation(pi_over_two);
	}

	EndGoalObject* end_goal = new EndGoalObject(glm::vec3(0.0f, 54.0f, 0.0f), sprite_, &sprite_shader_, tex_[boat], glm::vec2(3.5f), 3.0f);
	game_objects_.push_back(end_goal);
	// Setup weakling objects
    for (int i = 0; i < 5; i++) {
        float x = (rand() % 24) - 12;
        float y = (rand() % 6) + 3;
        glm::vec3 goal = glm::vec3(0.0f, 68.0f, 0.0f);
        WeaklingObject* weakling_ = new WeaklingObject(glm::vec3(x, y, 0.0f), sprite_, &sprite_shader_, tex_[weakling], glm::vec2(1.0f, 1.0f), 0.5f, goal);
        weakling_->SetRotation(pi_over_two);
        end_goal->addWeakling(weakling_);
        game_objects_.push_back(weakling_);
    }

    // Setup background object
    // The background is always the last before object
    BackgroundGameObject* background = new BackgroundGameObject(glm::vec3(12.0f, 12.0f, 0.0f), sprite_, &sprite_shader_, tex_[tex_stars], glm::vec2(1.0f, 1.0f));
    background->SetScale(glm::vec2(12.0f, 12.0f));
    game_objects_.push_back(background);
        
    // Initialize hud
    hud_ = new HUD(&sprite_shader_, sprite_, tex_[nothing], dynamic_cast<PlayerGameObject*>(game_objects_[0]));
	DrawingGameObject* healthbar = new DrawingGameObject(glm::vec3(-0.9f, 0.8f, 0.0f), sprite_, &drawing_shader_, tex_[nothing], glm::vec2(0.0f, 0.0f));
	hud_->addHudElement(healthbar);
	TextGameObject* ammo_bullets = new TextGameObject(glm::vec3(0.0f, 0.0f, 0.0f), sprite_, &text_shader_, tex_[text]);
	ammo_bullets->SetText("Bullets: ");
	ammo_bullets->SetPos(glm::vec3(0.6f, -0.7f, 0.0f));
	ammo_bullets->SetScale(glm::vec2(0.5f, 0.1f));
	hud_->addHudElement(ammo_bullets);
	TextGameObject* ammo_rockets = new TextGameObject(glm::vec3(0.0f, 0.0f, 0.0f), sprite_, &text_shader_, tex_[text]);
	ammo_rockets->SetText("Rockets: ");
	ammo_rockets->SetPos(glm::vec3(0.6f, -0.8f, 0.0f));
    ammo_rockets->SetScale(glm::vec2(0.5f, 0.1f));
	hud_->addHudElement(ammo_rockets);

	spawn_timer = new Timer();
}


void Game::DestroyGameWorld(void)
{
    // Free memory for all objects
    // Only need to delete objects that are not automatically freed
    for (int i = 0; i < game_objects_.size(); i++){
        delete game_objects_[i];
    }
}


void Game::HandleControls(double delta_time)
{
    // Get player game object
    PlayerGameObject* player = dynamic_cast<PlayerGameObject*>(game_objects_[0]);
    // Get current position and angle
    glm::vec3 curpos = player->GetPosition();
    float angle = player->GetRotation();
    // Compute current bearing direction
    glm::vec3 dir = player->GetBearing();
    // Adjust motion increment and angle increment 
    // if translation or rotation is too slow
    float speed = delta_time*1200.0;
    float motion_increment = 0.001*speed;
    float angle_increment = (glm::pi<float>() / 1800.0f)*speed;

    // Check for player input and make changes accordingly
    // Only if the player is not dying
    if (!player->isDying()) {
        if (glfwGetKey(window_, GLFW_KEY_W) == GLFW_PRESS) {
            //player->SetPosition(curpos + motion_increment * dir);
			player->update_velocity(0);
        }
        if (glfwGetKey(window_, GLFW_KEY_S) == GLFW_PRESS) {
            //player->SetPosition(curpos - motion_increment * dir);
			player->update_velocity(1);
        }
        if (glfwGetKey(window_, GLFW_KEY_D) == GLFW_PRESS) {
            player->SetRotation(angle - (angle_increment * std::min(player->get_velocity(), 1.0f)));
        }
        if (glfwGetKey(window_, GLFW_KEY_A) == GLFW_PRESS) {
            player->SetRotation(angle + (angle_increment * std::min(player->get_velocity(), 1.0f)));
        }
        if (glfwGetKey(window_, GLFW_KEY_1) == GLFW_PRESS) {
			GunComponent* gun = dynamic_cast<GunComponent*>(player->getComponent(1));
			gun->setState(0);
        }
        if (glfwGetKey(window_, GLFW_KEY_2) == GLFW_PRESS) {
            GunComponent* gun = dynamic_cast<GunComponent*>(player->getComponent(1));
            gun->setState(1);
        }
		if (glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			GunComponent* gun = dynamic_cast<GunComponent*>(player->getComponent(1));
            if (!gun->cooling_down() && gun->hasAmmo()) {
				switch(gun->getState()) {
					case 0:
                        game_objects_.insert(game_objects_.begin() + 1, new BulletProjectile(gun->GetPosition(), gun->GetBearing(), sprite_, &sprite_shader_, tex_[8], glm::vec2(0.2, 0.2), 8.0f, 1, 5.0f, 0.1f));
						break;
					case 1:
						game_objects_.insert(game_objects_.begin() + 1, new MissileProjectile(gun->GetPosition(), gun->GetBearing(), sprite_, &sprite_shader_, tex_[9], glm::vec2(0.8, 0.5), 5.0f, 1, 5.0f, 0.2f));
						break;
				}
                player->shoot_projectile();
            }
        }
        if (glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window_, true);
        }
    }
}


void Game::Update(double delta_time)
{
    float pi_over_two = glm::pi<float>() / 2.0f;
	// If spawn timer is finished, spawn a new object in random location
    if (spawn_timer->Finished() || !spawn_timer->Running()) {
        SpawnObject();
	}
    // Casts the current game object to a player object, allows use of Player specific functions
    PlayerGameObject* player = dynamic_cast<PlayerGameObject*>(game_objects_[0]);
    // Update all game objects
    for (int i = 0; i < game_objects_.size(); i++) {
        // Get the current game object
        GameObject* current_game_object = game_objects_[i];
		// Evaluate if the current game object is a projectile object
        ProjectileGameObject* projectile_curr = dynamic_cast<ProjectileGameObject*>(current_game_object);
        EnemyProjectileObject* ranged_enemy_proj = dynamic_cast<EnemyProjectileObject*>(current_game_object);
		// Evaluate if the current game object is an explosion object
		Explosion* exp = dynamic_cast<Explosion*>(current_game_object);
        // Evaluate if the current game object is a ranged enemy object
        RangedEnemyObject* ranged_enemy_curr = dynamic_cast<RangedEnemyObject*>(current_game_object);

        KamikazeEnemyObject* kamikaze_enemy_curr = dynamic_cast<KamikazeEnemyObject*>(current_game_object);

		WeaklingObject* weakling_curr = dynamic_cast<WeaklingObject*>(current_game_object);

		EndGoalObject* end_goal_curr = dynamic_cast<EndGoalObject*>(current_game_object);
        // Check if the object is dying
        if (current_game_object->isDying()) {
            // If the object is dying, check if the timer has finished
            if (current_game_object->timer->Finished()) {
                // If player dies, comment "Game over" and close the window
                if (current_game_object == player) {
                    std::cout << "Game over" << std::endl;
                    glfwSetWindowShouldClose(window_, true);
                    return;
                }
                if (kamikaze_enemy_curr) {
                    Explosion* exp_ = new Explosion(current_game_object->GetPosition(), sprite_, &sprite_shader_, tex_[10], glm::vec2(1.0f, 1.0f), 10.0f, 1.5);
                    GameObject* particles = new ParticleSystem(glm::vec3(-0.5f, 0.0f, 0.0f), particles_, &explosion_shader_, tex_[4], exp_);
                    particles->SetScale(glm::vec2(0.2f));
                    particles->SetRotation(-pi_over_two);
                    particle_systems_.push_back(particles);
                    game_objects_.insert(game_objects_.begin() + i + 1, exp_);
                    exp_->timer->Start(1);
                    particles->timer->Start(1);
                }
                // If the timer has finished, remove the object from the game world
                game_objects_.erase(game_objects_.begin() + i);
                // Deletes dead object from memory
                delete current_game_object;
                // Makes sure that we don't call the deleted object by skipping the rest of the loop
                continue;
            }
            if (current_game_object == player)
                return;
        }

        // Update the current game object
        current_game_object->Update(delta_time);
        // Projectile handling
        if (projectile_curr && projectile_curr->timer->Finished()) {
            game_objects_.erase(game_objects_.begin() + i);
            delete current_game_object;
            continue;
        }
        if(ranged_enemy_curr && !ranged_enemy_curr->isDying() && ranged_enemy_curr->inRange(player->GetPosition())) {
            ranged_enemy_curr->updatePlayerPos(player->GetPosition());

            // Calculate direction vectors
            glm::vec3 player_pos = player->GetPosition();
            glm::vec3 enemy_pos = ranged_enemy_curr->GetPosition();
            glm::vec3 direction_to_player = glm::normalize(player_pos - enemy_pos);

            glm::vec3 enemy_forward = glm::vec3(cos(ranged_enemy_curr->GetRotation()), sin(ranged_enemy_curr->GetRotation()), 0.0f);

            // Normalize vectors
            enemy_forward = glm::normalize(enemy_forward);

            // Calculate dot product
            float dot_product = glm::dot(direction_to_player, enemy_forward);

            // Calculate angle
            float angle = acos(dot_product);
            float angle_degrees = glm::degrees(angle);

            // Player is within ±30 degrees of where the enemy is looking
            if (ranged_enemy_curr->getShootTimer()->Finished()) {
                game_objects_.insert(game_objects_.begin() + 1, new EnemyProjectileObject(ranged_enemy_curr->GetPosition(), ranged_enemy_curr->GetBearing(), sprite_, &sprite_shader_, tex_[8], glm::vec2(0.2, 0.2), 8.0f, 1, 5.0f, 0.1f));
                ranged_enemy_curr->getShootTimer()->Start(2);
            }
        }

        // Check for collision with other game objects
        // Note the loop bounds: we avoid testing the last 9 objects since
        // they are the background covering the whole game world
        for (int j = i + 1; j < (game_objects_.size() - BACKGROUND_OBJECTS); j++) {
            GameObject* other_game_object = game_objects_[j];
			// Evaluate if the other game object is an enemy object
            EnemyGameObject* enemy = dynamic_cast<EnemyGameObject*>(other_game_object);
            // Evaluate if the other game object is a Collider Object
            ColliderObject* collider = dynamic_cast<ColliderObject*>(other_game_object);
			// Evaluate if other game object is a collectible object
			CollectibleGameObject* collectible = dynamic_cast<CollectibleGameObject*>(other_game_object);
			// Evaluate if other game object is an explosion
			Explosion* exp_other = dynamic_cast<Explosion*>(other_game_object);
			WeaklingObject* weakling_other = dynamic_cast<WeaklingObject*>(other_game_object);
			EndGoalObject* end_goal_other = dynamic_cast<EndGoalObject*>(other_game_object);
            // Compute distance between object i and object j
            float distance = glm::length(current_game_object->GetPosition() - other_game_object->GetPosition());

            if (kamikaze_enemy_curr && !kamikaze_enemy_curr->isDying() && (weakling_other || other_game_object == player)) {
                if (kamikaze_enemy_curr->inRange(other_game_object->GetPosition())) {
                    kamikaze_enemy_curr->die();
                }
            }
            if (current_game_object == player) {
                if (collider && player->collide(collider)) {
                    // Checks to see if the object that it is currently colliding with the player is new
                    if (!other_game_object->isDying() && current_game_object->prev_collider != other_game_object) {
						if (collectible && !collectible->getGhostMode()) {
							// If the object is a collectible object, collect it
                            player->collect(collectible->getType());
							// Sets the object to ghost mode
							game_objects_.erase(game_objects_.begin() + j);
							delete other_game_object;
						}
						else if(!player->isDying() && enemy){
							// Deals damage to the player and the object that the player collided with
							current_game_object->prev_collider = other_game_object;
							other_game_object->hurt();
                            // Only damage player if they are not invincible
                            if (!player->is_invincible()) {
                                current_game_object->hurt();
                            }
						}
                    }
                }
				else if (enemy)
					// If the object is an enemy object, update the player's position
                    enemy->updatePlayerPos(player->GetPosition());
                // Resets the prev collider for the player if they leave the objects collision area
                // This is to ensure that only 1 health is removed per collision
                else if(other_game_object == player->prev_collider)
                    current_game_object->prev_collider = nullptr;
            }
            else if (ranged_enemy_curr && weakling_other && ranged_enemy_curr->inRange(weakling_curr->GetPosition())) {
				ranged_enemy_curr->updatePlayerPos(weakling_curr->GetPosition());
				// Calculate direction vectors
				glm::vec3 player_pos = weakling_curr->GetPosition();
				glm::vec3 enemy_pos = ranged_enemy_curr->GetPosition();
				glm::vec3 direction_to_player = glm::normalize(player_pos - enemy_pos);
				glm::vec3 enemy_forward = glm::vec3(cos(ranged_enemy_curr->GetRotation()), sin(ranged_enemy_curr->GetRotation()), 0.0f);
				// Normalize vectors
				enemy_forward = glm::normalize(enemy_forward);
				// Calculate dot product
				float dot_product = glm::dot(direction_to_player, enemy_forward);
				// Calculate angle
				float angle = acos(dot_product);
				float angle_degrees = glm::degrees(angle);
				// Player is within ±30 degrees of where the enemy is looking
                if (ranged_enemy_curr->getShootTimer()->Finished()) {
                    game_objects_.insert(game_objects_.begin() + 1, new EnemyProjectileObject(ranged_enemy_curr->GetPosition(), ranged_enemy_curr->GetBearing(), sprite_, &sprite_shader_, tex_[8], glm::vec2(0.2, 0.2), 8.0f, 1, 5.0f, 0.1f));
                    ranged_enemy_curr->getShootTimer()->Start(2);
                }
            }
            else if (projectile_curr && !ranged_enemy_proj) {
				//check if enemy is colliding with projectile
                if (enemy && projectile_curr->collide(enemy) && !enemy->isDying()) {
					BulletProjectile* bull = dynamic_cast<BulletProjectile*>(current_game_object);
                    MissileProjectile* miss = dynamic_cast<MissileProjectile*>(current_game_object);
					if (bull) {
						// If the object is a bullet projectile, deal damage to the enemy
						enemy->hurt();
                        // Add blood particles
                        GameObject* blood = new Blood(projectile_curr->GetPosition(), sprite_, &sprite_shader_);
                        blood->SetRotation(projectile_curr->GetRotation() + glm::pi<float>());
                        game_objects_.insert(game_objects_.begin() + 1, blood);
                        GameObject* particles = new ParticleSystem(glm::vec3(-0.5f, 0.0f, 0.0f), blood_particles_, &explosion_shader_, tex_[11], blood);
                        particles->SetScale(glm::vec2(0.05f));
                        particles->SetRotation(-pi_over_two);
                        particle_systems_.push_back(particles);
                        particles->timer->Start(1);
                        // Remove the projectile from the game world
					    game_objects_.erase(game_objects_.begin() + i + 1);
					    delete current_game_object;
					}
					else if (miss) {
						// If the object is a missile projectile, create an explosion
						Explosion * exp_ = new Explosion(current_game_object->GetPosition(), sprite_, &sprite_shader_, tex_[10], glm::vec2(1.0f, 1.0f), 10.0f, 1.5);
                        GameObject* particles = new ParticleSystem(glm::vec3(-0.5f, 0.0f, 0.0f), particles_, &explosion_shader_, tex_[4], exp_);
                        particles->SetScale(glm::vec2(0.2f));
                        particles->SetRotation(-pi_over_two);
						particle_systems_.push_back(particles);
						game_objects_.insert(game_objects_.begin() + 1, exp_);
					    // Remove the projectile from the game world
                        game_objects_.erase(game_objects_.begin() + i + 1);
                        delete current_game_object;
                        exp_->timer->Start(1);
						particles->timer->Start(1);
					}
                    break;
                }
            }
            else if (ranged_enemy_proj) {
                if ((ranged_enemy_proj->collide(player) && !player->isDying())) {
					// If the object is a ranged enemy projectile, deal damage to the player
					player->hurt();
					// Remove the projectile from the game world
					game_objects_.erase(game_objects_.begin() + i);
					delete current_game_object;
                    break;
                }
                else if (weakling_curr && ranged_enemy_proj->collide(weakling_curr) && !weakling_curr->isDying()) {
					weakling_curr->hurt();
					// Remove the projectile from the game world
					game_objects_.erase(game_objects_.begin() + i);
					delete current_game_object;
					break;
                }
            }
            else if (exp && (enemy || weakling_other) && !exp_other && !exp->IsDamaged(other_game_object)) {
				float distance = glm::length(current_game_object->GetPosition() - other_game_object->GetPosition());
				// Check if the object is within the explosion radius
                if (distance <= exp->GetRadius()) {
					// Add the object to the set of affected objects
					exp->AddAffectedObject(other_game_object);
                    // If the object is within the explosion radius, deal damage to the object
                    int damage = std::ceil(exp->GetDamageAt(distance));
                    for (int i = 0; i < damage; i++) {
                        other_game_object->hurt();
                        if(other_game_object->isDying())
							break;
                    }
                }
            }
            else if (current_game_object == player && exp_other && !exp_other->IsDamaged(player)){
				float distance = glm::length(current_game_object->GetPosition() - other_game_object->GetPosition());
				// Check if the object is within the explosion radius
                if (distance <= exp_other->GetRadius()) {
					// Add the object to the set of affected objects
					exp_other->AddAffectedObject(player);
					// If the object is within the explosion radius, deal damage to the object
					int damage = std::ceil(exp_other->GetDamageAt(distance));
                    for (int i = 0; i < damage; i++) {
                        player->hurt();
                        if (player->isDying())
                            break;
                    }
                }
            }
            else if (weakling_other && end_goal_curr && end_goal_curr->collide(weakling_other) && !weakling_other->isDying()) {
				std::cout << "Weakling reached end goal" << std::endl;
                weakling_other->reachEnd();
                end_goal_curr->addWeakling(weakling_other);
                switch (end_goal_curr->checkEndGoal()) {
                case 1:
					std::cout << "You win!" << std::endl;
					glfwSetWindowShouldClose(window_, true);
					return;
                case 2:
					std::cout << "You lose!" << std::endl;
					glfwSetWindowShouldClose(window_, true);
					return;
                }
            }
        }
    }
	// Update all particle systems
	for (int i = 0; i < particle_systems_.size(); i++) {
		ParticleSystem* particles = dynamic_cast<ParticleSystem*>(particle_systems_[i]);
		if (particles->timer->Finished()) {
			particle_systems_.erase(particle_systems_.begin() + i);
			delete particles;
		}
	}

    hud_->Update(delta_time);
}


void Game::Render(void){

    // Clear background
    glClearColor(viewport_background_color_g.r,
                 viewport_background_color_g.g,
                 viewport_background_color_g.b, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use aspect ratio to properly scale the window
    int width, height;
    glfwGetWindowSize(window_, &width, &height);
    glm::mat4 window_scale_matrix;
    if (width > height){
        float aspect_ratio = ((float) width)/((float) height);
        window_scale_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f/aspect_ratio, 1.0f, 1.0f));
    } else {
        float aspect_ratio = ((float) height)/((float) width);
        window_scale_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f/aspect_ratio, 1.0f));
    }

    // Set view to zoom out, centered by default at 0,0
    float camera_zoom = 0.2f;
    glm::mat4 camera_zoom_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(camera_zoom, camera_zoom, camera_zoom));
	glm::mat4 camera_translation_matrix = glm::translate(glm::mat4(1.0f), -game_objects_[0]->GetPosition());
    glm::mat4 view_matrix = window_scale_matrix * camera_zoom_matrix * camera_translation_matrix;

    // Render hud and hud elms
    glm::mat4 ortho_matrix = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);
    hud_->Render(ortho_matrix, current_time_);
    // Render all game objects
    for (int i = 0; i < game_objects_.size(); i++) {
        game_objects_[i]->Render(view_matrix, current_time_);
    }
	// Render all particle systems
	for (int i = 0; i < particle_systems_.size(); i++) {
		particle_systems_[i]->Render(view_matrix, current_time_);
	}
}


void Game::MainLoop(void)
{
    // Loop while the user did not close the window
    double last_time = glfwGetTime();
    spawn_timer = new Timer();
	spawn_timer->Start(2);
    while (!glfwWindowShouldClose(window_)){

        // Calculate delta time
        current_time_ = glfwGetTime();
        double delta_time = current_time_ - last_time;
        last_time = current_time_;

        // Update window events like input handling
        glfwPollEvents();

        // Handle user input
        HandleControls(delta_time);

        // Update all the game objects
        Update(delta_time);

        // Render all the game objects
        Render();

        // Push buffer drawn in the background onto the display
        glfwSwapBuffers(window_);
    }
}


Game::Game(void)
{
    // Don't do work in the constructor, leave it for the Init() function
}


void Game::Init(void)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Initialize the window management library (GLFW)
    if (!glfwInit()) {
        throw(std::runtime_error(std::string("Could not initialize the GLFW library")));
    }

    // Set whether window can be resized
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE); 

    // Create a window and its OpenGL context
    window_ = glfwCreateWindow(window_width_g, window_height_g, window_title_g, NULL, NULL);
    if (!window_) {
        glfwTerminate();
        throw(std::runtime_error(std::string("Could not create window")));
    }

    // Make the window's OpenGL context the current one
    glfwMakeContextCurrent(window_);

    // Initialize the GLEW library to access OpenGL extensions
    // Need to do it after initializing an OpenGL context
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        throw(std::runtime_error(std::string("Could not initialize the GLEW library: ") + std::string((const char *)glewGetErrorString(err))));
    }

    // Set event callbacks
    glfwSetFramebufferSizeCallback(window_, ResizeCallback);

    // Initialize sprite geometry
    sprite_ = new Sprite();
    sprite_->CreateGeometry();

    // Initialize particle geometry
    Particles* particles_temp = new Particles();
    particles_temp->CreateGeometry(4000); // Use 4000 particles
    particles_ = particles_temp;

	// Initialize blood particle geometry
	BloodParticles* blood_temp = new BloodParticles();
	blood_temp->CreateGeometry(64); // Use 64 particles
	blood_particles_ = blood_temp;

    // Initialize sprite shader
    sprite_shader_.Init((resources_directory_g+std::string("/sprite_vertex_shader.glsl")).c_str(), (resources_directory_g+std::string("/sprite_fragment_shader.glsl")).c_str());
    // Initialize particle shader
    explosion_shader_.Init((resources_directory_g + std::string("/explosion_vertex_shader.glsl")).c_str(), (resources_directory_g + std::string("/particle_fragment_shader.glsl")).c_str());
	// Initialize blood shader
	blood_shader_.Init((resources_directory_g + std::string("/blood_vertex_shader.glsl")).c_str(), (resources_directory_g + std::string("/particle_fragment_shader.glsl")).c_str());
    // Initialize the drawing shader
	drawing_shader_.Init((resources_directory_g + std::string("/sprite_vertex_shader.glsl")).c_str(), (resources_directory_g + std::string("/drawing_fragment_shader.glsl")).c_str());
    // Initialize the text shader
	text_shader_.Init((resources_directory_g + std::string("/sprite_vertex_shader.glsl")).c_str(), (resources_directory_g + std::string("/text_fragment_shader.glsl")).c_str());

    // Initialize time
    current_time_ = 0.0;
}


Game::~Game()
{
    // Free memory used by game world
    DestroyGameWorld();

    // Free rendering resources
    delete sprite_;
    delete particles_;
	delete blood_particles_;

    // Close window
    glfwDestroyWindow(window_);
    glfwTerminate();
}


void Game::ResizeCallback(GLFWwindow* window, int width, int height)
{

    // Set OpenGL viewport based on framebuffer width and height
    glViewport(0, 0, width, height);
}


void Game::SetTexture(GLuint w, const char *fname)
{
    // Bind texture buffer
    glBindTexture(GL_TEXTURE_2D, w);

    // Load texture from a file to the buffer
    int width, height;
    unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGBA);
    if (!image){
        std::cout << "Cannot load texture " << fname << std::endl;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);

    // Texture Wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Texture Filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


void Game::LoadTextures(std::vector<std::string> &textures)
{
    // Allocate a buffer for all texture references
    int num_textures = textures.size();
    tex_ = new GLuint[num_textures];
    glGenTextures(num_textures, tex_);
    // Load each texture
    for (int i = 0; i < num_textures; i++){
        SetTexture(tex_[i], (resources_directory_g+textures[i]).c_str());
    }
    // Set first texture in the array as default
    glBindTexture(GL_TEXTURE_2D, tex_[0]);
}

// Spawns a new object in the game world in a random location
void Game::SpawnObject() {
    //std::cout << "spawing object" << std::endl;
    float pi_over_two = glm::pi<float>() / 2.0f;
    // Randomly generate a location for the new object
	float x = (rand() % 30) - 15;
	float y = (rand() % 30) - 15;
    int random = rand() % 10;
    if (random == 0) {
		KamikazeEnemyObject* new_enemy = new KamikazeEnemyObject(glm::vec3(x, y, 0.0f), sprite_, &sprite_shader_, tex_[1], glm::vec2(1.0f, 1.0f), 0.4f);
		new_enemy->SetRotation(pi_over_two);
		game_objects_.insert(game_objects_.begin() + game_objects_.size() - BACKGROUND_OBJECTS, new_enemy);
    }
	else if (random >= 1 && random <= 5) {
		std::cout << "spawning wanderer" << std::endl;
		WanderingEnemyObject* new_enemy = new WanderingEnemyObject(glm::vec3(x, y, 0.0f), sprite_, &sprite_shader_, tex_[16], glm::vec2(1.0f, 1.0f), 0.4f);
		new_enemy->SetRotation(pi_over_two);
		game_objects_.insert(game_objects_.begin() + game_objects_.size() - BACKGROUND_OBJECTS, new_enemy);
	}
	else {
		RangedEnemyObject* new_enemy = new RangedEnemyObject(glm::vec3(x, y, 0.0f), sprite_, &sprite_shader_, tex_[2], glm::vec2(1.0f, 1.0f), 0.4f);
		new_enemy->SetRotation(pi_over_two);
		game_objects_.insert(game_objects_.begin() + game_objects_.size() - BACKGROUND_OBJECTS, new_enemy);
	}
	// Restart the spawn timer
	spawn_timer->Start(2.0f);
}

} // namespace game
