#pragma once
#include "Object3d.h"

class CarAmbo
{
	Object3d obj;

public:
	CarAmbo();
	~CarAmbo();
	void initialize();
	void update();
	void render();
	void release();
	void extractDepthmap();
};

