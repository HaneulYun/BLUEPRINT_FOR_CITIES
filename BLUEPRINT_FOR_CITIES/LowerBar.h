#pragma once
#include "ObjectUI.h"

class LowerBar
{
	ObjectUI obj;
public:
	LowerBar();
	~LowerBar();
	void initialize();
	void update();
	void render();
	void release();
};