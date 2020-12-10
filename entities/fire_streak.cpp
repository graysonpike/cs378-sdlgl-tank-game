#include <iostream>

#include "fire_streak.h"


FireStreak::FireStreak(Scene *scene, std::pair<int, int> start, std::pair<int, int> end, float duration) :
	PhysicalEntity(scene, start.first, start.second, 0, 0),
	end_x(end.first),
	end_y(end.second),
	timer(duration) {
		timer.reset();
}


void FireStreak::update() {
	if (timer.is_done()) {
		kill();
	}
}


void FireStreak::render() {
	SDL_Renderer *renderer = scene->get_graphics()->get_renderer();
	int opacity = (int)(timer.remaining() * 255);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, opacity);
	SDL_RenderDrawLine(renderer, x, y, end_x, end_y);
}