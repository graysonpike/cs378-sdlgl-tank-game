#include <utility>
#include <iostream>
#include <math.h>
#include <sdlgl/graphics/resources.h>

#include "tank.h"


std::pair<int, int> rotate_vector(int magnitude, float angle) {
    int x = magnitude * sin(angle);
    int y = -magnitude * cos(angle);
    return std::pair<int, int>(x, y);
}


Tank::Tank(Scene *scene, float x, float y) :
    PhysicalEntity(scene, x, y, 60, 114) {

    Resources *resources = scene->get_graphics()->get_resources();

    textures["hull"] = resources->get_texture("sherman_hull");
    textures["turret"] = resources->get_texture("sherman_turret");
    textures["barrel"] = resources->get_texture("sherman_barrel");
}


void Tank::drive(bool direction, bool turn_left, bool turn_right) {}

void Tank::rotate_turret(bool direction) {}

void Tank::fire() {}

void Tank::update() {}

void Tank::render() {
    textures["hull"].draw(scene, x, y, hull_angle);
    std::pair<int, int> barrel_offset_position = rotate_vector(barrel_offset, turret_angle);
    textures["barrel"].draw(scene, barrel_offset_position.first + x, barrel_offset_position.second + y, turret_angle);
    std::pair<int, int> turret_offset_position = rotate_vector(turret_offset, hull_angle);
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