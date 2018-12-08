#pragma once
#include "ObjectUI.h"

class Faster
{
	ObjectUI obj;

public:
	Faster();
	~Faster();
	void initialize();
	void update();
	void render();
	void release();

	bool faster;
};

