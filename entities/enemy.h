#ifndef ENEMY_H
#define ENEMY_H

#include "tiger.h"
#include "player.h"


class Enemy : public Tiger {

	Player *player;

	void handle_driving();
	void handle_turret();
	void handle_fire();

public:
	Enemy(Scene *scene, float x, float y);
	void update();
};

#endif