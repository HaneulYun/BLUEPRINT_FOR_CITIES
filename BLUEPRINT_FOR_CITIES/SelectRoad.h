#pragma once
#include "ObjectUI.h"

class SelectRoad
{
	ObjectUI mainobj;

	ObjectUI subS;
	ObjectUI subC;
public:
	SelectRoad();
	~SelectRoad();
	void initialize();
	void update();
	void render();
	void release();

	bool select;
};