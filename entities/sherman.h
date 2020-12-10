#ifndef SHERMAN_H
#define SHERMAN_H

#include "tank.h"


class Sherman : public Tank {

	void load_resources();

public:
	Sherman(Scene *scene, float x, float y);
};

#endif