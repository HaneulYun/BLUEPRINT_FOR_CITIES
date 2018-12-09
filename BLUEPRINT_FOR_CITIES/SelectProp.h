#pragma once
#include "ObjectUI.h"

class SelectProp
{
	ObjectUI mainobj;
public:
	SelectProp();
	~SelectProp();
	void initialize();
	void update();
	void render();
	void release();

	bool select;
};