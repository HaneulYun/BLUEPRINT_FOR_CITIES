#pragma once
#include "Object3d.h"

class Cloud
{
	Object3d obj;
public:
	Cloud();
	~Cloud();
	void initialize();
	void update();
	void render();
	void release();
};