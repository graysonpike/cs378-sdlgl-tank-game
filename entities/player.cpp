#include "player.h"
#include <iostream>

#define KEY_MOVE_FORWARD  SDL_SCANCODE_W
#define KEY_MOVE_BACKWARD SDL_SCANCODE_S
#define KEY_TURN_LEFT     SDL_SCANCODE_A
#define KEY_TURN_RIGHT    SDL_SCANCODE_D
#define KEY_TURRET_LEFT   SDL_SCANCODE_LEFT
#define KEY_TURRET_RIGHT  SDL_SCANCODE_RIGHT
#define KEY_FIRE          SDL_SCANCODE_SPACE


Player::Player(Scene *scene, float x, float y) : Sherman(scene, x, y) {}

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


void Player::update() {
    handle_inputs(scene->get_inputs());
    Sherman::update();
}