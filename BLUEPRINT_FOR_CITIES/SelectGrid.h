#pragma once
#include "ObjectUI.h"

class SelectGrid
{
	ObjectUI mainobj;
public:
	SelectGrid();
	~SelectGrid();
	void initialize();
	void update();
	void render();
	void release();

	bool select;
};