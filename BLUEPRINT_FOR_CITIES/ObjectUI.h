#pragma once
#include "Object.h"

class ObjectUI : public Object
{
public:
	ObjectUI();
	~ObjectUI();

	void initialize();
	void update();
	void render();
	void release();
};

