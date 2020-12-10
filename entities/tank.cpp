#include <utility>
#include <iostream>
#include <sdlgl/graphics/resources.h>
#include <sdlgl/graphics/effects/particles.h>
#include <sdlgl/utilities/math.h>

#include "tank.h"
#include "fire_streak.h"


const float Tank::forward_driving_speed = 80.0f;
const float Tank::stationary_turn_forward_speed = 15.0f;
const float Tank::backward_driving_speed = 60.0f;
const float Tank::turning_speed = 1.0f;
const int Tank::gun_recoil_amount = 10;
const int Tank::turret_offset = 0;
const int Tank::barrel_tip_offset = 70;


Tank::Tank(Scene *scene, float x, float y, int w, int h) :
    PhysicalEntity(scene, x, y, w, h) {
        barrel_offset = 40;
        turret_speed = 1.0f;
}

void Tank::drive(bool direction) {
    if (direction) {
        driving_state = DrivingState::FORWARD;
    } else {
        driving_state = DrivingState::BACKWARD;
    }
}

void Tank::turn(bool direction) {
    if (direction) {
        turning_state = TurningState::RIGHT;
    } else {
        turning_state = TurningState::LEFT;
    }
}

void Tank::rotate_turret(bool direction) {
    turret_angle += turret_speed * (direction ? 1 : -1) * scene->get_delta();
}

void Tank::fire() {
    if (!reload_timer.is_done()) {
        return;
    }
    // Fire gun
    reload_timer.reset();
    recoil_timer.reset();
    fire_sound.play();
    std::pair<int, int> fire_endpoint = get_fire_endpoint();
    scene->add_entity(new FireStreak(scene, std::pair<int, int>(x, y), fire_endpoint));
    std::vector<SDL_Color> explosion_colors;
    explosion_colors.push_back({50, 50, 50});
    explosion_colors.push_back({100, 100, 100});
    explosion_colors.push_back({150, 150, 150});
    explosion_colors.push_back({255, 87, 69});
    explosion_colors.push_back({255, 168, 69});
    explosion_colors.push_back({255, 209, 69});
    std::pair<int, int> offset_vector = Math::rotate_vector(barrel_tip_offset, turret_angle);
    scene->add_entity(new Particles(scene, x + offset_vector.first, y + offset_vector.second, -100, 100, -100, 100, explosion_colors, 50, 4, 0.3f, 0.1f, false));
    scene->add_entity(new Particles(scene, fire_endpoint.first, fire_endpoint.second, -100, 100, -100, 100, explosion_colors, 50, 4, 0.3f, 0.1f, false));
}

std::pair<int, int> Tank::get_fire_endpoint() {
    std::pair<int, int> offset_vector = Math::rotate_vector(250, turret_angle);
    return std::pair<int, int>(x + offset_vector.first, y + offset_vector.second);
}

void Tank::move() {
    float speed = 0;
    float turn_angle = 0;
    float delta = scene->get_delta();
    if (driving_state == DrivingState::FORWARD) {
        if (turning_state == TurningState::RIGHT) {
            turn_angle = turning_speed;
        } else if (turning_state == TurningState::LEFT) {
            turn_angle = -turning_speed;
        }
        speed = forward_driving_speed;
    }
    if (driving_state == DrivingState::BACKWARD) {
        if (turning_state == TurningState::RIGHT) {
            turn_angle = -turning_speed;
        } else if (turning_state == TurningState::LEFT) {
            turn_angle = turning_speed;
        }
        speed = -backward_driving_speed;
    }
    if (driving_state == DrivingState::NOT_DRIVING) {
        if (turning_state == TurningState::RIGHT) {
            turn_angle = turning_speed;
        } else if (turning_state == TurningState::LEFT) {
            turn_angle = -turning_speed;
        }
        if (turning_state != TurningState::NOT_TURNING) {
            // Apply some forward speed when turning
            speed = stationary_turn_forward_speed;
        }
    }
    y += speed * sin(hull_angle - M_PI/2) * delta;
    x += speed * cos(hull_angle - M_PI/2) * delta;
    hull_angle += turn_angle * delta;
    turret_angle += turn_angle * delta;
}

void Tank::update() {
    move();
    driving_state = DrivingState::NOT_DRIVING;
    turning_state = TurningState::NOT_TURNING;
}

void Tank::render() {

    textures["hull"].draw(scene, x, y, hull_angle);

    // Handle recoil on gun barrel
    float recoil_offset = 0.0f;
    if (!recoil_timer.is_done()) 
{        recoil_offset = (recoil_timer.remaining()) * gun_recoil_amount;
    }
    std::pair<int, int> barrel_offset_position = Math::rotate_vector(barrel_offset - recoil_offset, turret_angle);
    textures["barrel"].draw(scene, barrel_offset_position.first + x, barrel_offset_position.second + y, turret_angle);

    std::pair<int, int> turret_offset_position = Math::rotate_vector(turret_offset, hull_angle);
    textures["turret"].draw(scene, turret_offset_position.first + x, turret_offset_position.second + y, turret_angle);

    // Debug Graphics
    SDL_Renderer *renderer = scene->get_graphics()->get_renderer();
    if (scene->get_graphics()->get_debug_visuals_enabled()) {
        // Draw red point in center of tank
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect box_rect = {(int)x-2, (int)y-2, 4, 4};
        SDL_RenderFillRect(renderer, &box_rect);
    }
}