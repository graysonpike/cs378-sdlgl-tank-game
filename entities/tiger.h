#ifndef TIGER_H
#define TIGER_H

#include "tank.h"


class Tiger : public Tank {

	void load_resources();

public:
	Tiger(Scene *scene, float x, float y);
	
};

#endif