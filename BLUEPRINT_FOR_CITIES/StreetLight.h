#pragma once
#include "Object3d.h"

class StreetLight
{
	Object3d obj;

public:
	StreetLight();
	~StreetLight();
	void initialize();
	void update();
	void render();
	void release();
	void extractDepthmap();
};

