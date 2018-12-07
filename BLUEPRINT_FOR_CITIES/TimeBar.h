#pragma once
#include "ObjectUI.h"

class TimeBar
{
	ObjectUI obj;
public:
	TimeBar();
	~TimeBar();
	void initialize();
	void update();
	void render();
	void release();
};