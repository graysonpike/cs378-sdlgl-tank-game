#ifndef FIRESTREAK_H
#define FIRESTREAK_H

#include <utility>

#include <sdlgl/game/physical_entity.h>
#include <sdlgl/game/timer.h>


class FireStreak : public PhysicalEntity {

	int end_x;
	int end_y;
	Timer timer;

public:
	FireStreak(Scene *scene, std::pair<int, int> start, std::pair<int, int> end, float duration=1.0f);
	void update();
	void render();
};


#endif