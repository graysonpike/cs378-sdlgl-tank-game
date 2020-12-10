#include "sherman.h"

#include "../util/math.h"


Sherman::Sherman(Scene *scene, float x, float y) : Tank(scene, x, y, 60, 114) {
	load_resources();
}


void Sherman::load_resources() {

    Resources *resources = scene->get_graphics()->get_resources();

    textures["hull"] = resources->get_texture("sherman_hull");
    textures["turret"] = resources->get_texture("sherman_turret");
    textures["barrel"] = resources->get_texture("sherman_barrel");

    fire_sound = resources->get_sound("sherman_fire");
}
