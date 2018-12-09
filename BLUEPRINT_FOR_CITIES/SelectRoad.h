#pragma once
#include "ObjectUI.h"

class SelectRoad
{
	ObjectUI mainobj;
public:
	SelectRoad();
	~SelectRoad();
	void initialize();
	void update();
	void render();
	void release();

	bool select;
};