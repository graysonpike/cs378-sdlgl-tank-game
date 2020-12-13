#ifndef HIT_COUNTER_H
#define HIT_COUNTER_H

#include <string>
#include <SDL2/SDL.h>

#include <sdlgl/game/entity.h>
#include <sdlgl/game/scene.h>
#include <sdlgl/graphics/graphics.h>

class HitCounter : public Entity {

	int hit_count;
	std::string font;
	SDL_Color color;

public:
	
	HitCounter(Scene *scene, std::string font, SDL_Color color);

	void increment();
	void update();
	void render();

};

#endif