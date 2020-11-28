#ifndef PLAYER_H
#define PLAYER_H

#include <sdlgl/game/entity.h>

#include "sherman.h"


class Player : public Sherman {

	void handle_inputs(Inputs *inputs);

public:
	Player(Scene *scene, float x, float y);
	void update();
};

#endif