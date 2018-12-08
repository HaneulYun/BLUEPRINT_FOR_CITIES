#pragma once
#include "Object3d.h"

class Hydrant
{

public:
	Object3d obj;
	Hydrant();
	~Hydrant();
	void initialize();
	void update();
	void render();
	void release();
};

