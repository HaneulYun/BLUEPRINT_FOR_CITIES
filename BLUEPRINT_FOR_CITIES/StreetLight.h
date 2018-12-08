#pragma once
#include "Object3d.h"

class StreetLight
{

public:
	Object3d obj;
	StreetLight();
	~StreetLight();
	void initialize();
	void update();
	void render();
	void release();
};

