#pragma once
#include "ObjectUI.h"

class TimeBar
{
	ObjectUI frame;
	ObjectUI bar;

public:
	TimeBar();
	~TimeBar();
	void initialize();
	void update();
	void render();
	void release();
};