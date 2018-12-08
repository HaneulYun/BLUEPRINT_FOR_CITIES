#pragma once
#include "ObjectUI.h"

class DestroyEffect
{
	ObjectUI frame;
	ObjectUI ppip;
public:
	DestroyEffect();
	~DestroyEffect();
	void initialize();
	void update();
	void render();
	void release();
};

