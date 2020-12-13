#ifndef PLAYER_H
#define PLAYER_H

#include <sdlgl/game/entity.h>

#include "sherman.h"
#include "enemy.h"

class Enemy;

class Player : public Sherman {

	Enemy *enemy;
	void handle_inputs(Inputs *inputs);

public:

	Player(Scene *scene, float x, float y);
	void fire();
	void update();
};

#endif