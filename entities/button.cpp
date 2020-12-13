#include <iostream>

#include "button.h"


Button::Button(Scene *scene, int x, int y, std::string image) :
	PhysicalEntity(scene, x, y, 0, 0) {

	Resources *resources = scene->get_graphics()->get_resources();
	texture = resources->get_texture(image);

}


void Button::update() {
}


void Button::render() {
	texture.draw(scene, x, y);
}