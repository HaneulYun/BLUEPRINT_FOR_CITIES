#pragma once
#include "ObjectUI.h"

class Pause
{
	ObjectUI obj;

public:
	Pause();
	~Pause();
	void initialize();
	void update();
	void render();
	void release();
};

