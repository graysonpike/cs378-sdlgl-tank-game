#include "player.h"
#include <iostream>
#include "hit_counter.h"

#define KEY_MOVE_FORWARD  SDL_SCANCODE_W
#define KEY_MOVE_BACKWARD SDL_SCANCODE_S
#define KEY_TURN_LEFT     SDL_SCANCODE_A
#define KEY_TURN_RIGHT    SDL_SCANCODE_D
#define KEY_TURRET_LEFT   SDL_SCANCODE_LEFT
#define KEY_TURRET_RIGHT  SDL_SCANCODE_RIGHT
#define KEY_FIRE          SDL_SCANCODE_SPACE


Player::Player(Scene *scene, float x, float y) : Sherman(scene, x, y) {
    enemy = nullptr;
}

void Player::handle_inputs(Inputs *inputs) {
    if (inputs->is_key_down(KEY_MOVE_FORWARD)) {
        drive(true);
    } else if (inputs->is_key_down(KEY_MOVE_BACKWARD)) {
        drive(false);
    }
    if (inputs->is_key_down(KEY_TURN_RIGHT)) {
        turn(true);
    } else if (inputs->is_key_down(KEY_TURN_LEFT)) {
        turn(false);
    }
    if (inputs->is_key_down(KEY_TURRET_RIGHT)) {
        rotate_turret(true);
    } else if (inputs->is_key_down(KEY_TURRET_LEFT)) {
        rotate_turret(false);
    }
    if (inputs->is_key_down_event(KEY_FIRE)) {
        fire();
    }
}


void Player::fire() {
    if (reload_timer.is_done()) {
        std::pair<int, int> fire_endpoint = get_fire_endpoint();
        if (enemy->get_hitbox()->check_point((SDL_Point){fire_endpoint.first, fire_endpoint.second})) {
            std::vector<Entity*> players = scene->get_entities_of_type(3);
            HitCounter *counter = static_cast<HitCounter*>(players[0]);
            counter->increment();
        }
    }
    Tank::fire();
}


void Player::update() {
    if (enemy == nullptr) {
        std::vector<Entity*> players = scene->get_entities_of_type(2);
        enemy = static_cast<Enemy*>(players[0]);
    }
    handle_inputs(scene->get_inputs());
    Sherman::update();
}