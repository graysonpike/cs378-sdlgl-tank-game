#ifndef BUTTON_H
#define BUTTON_H

#include <string>

#include <sdlgl/game/physical_entity.h>
#include <sdlgl/graphics/texture.h>


class Button : public PhysicalEntity {

	Texture texture;

public:
	Button(Scene *scene, int x, int y, std::string image);
	void update();
	void render();
};


#endif