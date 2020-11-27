#include <iostream>
#include <sdlgl/graphics/resources.h>

#include "tank.h"


Tank::Tank(Scene *scene, float x, float y) :
    PhysicalEntity(scene, x, y, 60, 114) {

    Resources *resources = scene->get_graphics()->get_resources();

    textures["hull"] = resources->get_texture("sherman_hull");
    textures["turret"] = resources->get_texture("sherman_turret");
    textures["barrel"] = resources->get_texture("sherman_barrel");
}


void Tank::drive(bool direction, bool turn_left, bool turn_right) {}

void Tank::fire() {}

void Tank::update() {}

void Tank::render() {
    textures["hull"].draw(scene, x, y);
}