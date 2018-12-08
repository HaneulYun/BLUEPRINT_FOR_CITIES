#pragma once
#include "Object.h"

class ObjectLight : public Object
{
public:
	ObjectLight();
	~ObjectLight();

	void initialize();
	void update();
	void render();
	void release();
};

