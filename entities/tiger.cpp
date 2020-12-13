#include "tiger.h"
#include <sdlgl/utilities/math.h>


Tiger::Tiger(Scene *scene, float x, float y) : Tank(scene, x, y, 60, 114) {
	load_resources();
	barrel_offset = 60;
	turret_speed = 0.3f;
}

void Tiger::load_resources() {

    Resources *resources = scene->get_graphics()->get_resources();

    textures["hull"] = resources->get_texture("tiger_hull");
    textures["turret"] = resources->get_texture("tiger_turret");
    textures["barrel"] = resources->get_texture("tiger_barrel");

    fire_sound = resources->get_sound("tiger_fire");
}
