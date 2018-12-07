#pragma once
#include "Object3d.h"

class TopBar
{
	Object3d obj;
public:
	TopBar();
	~TopBar();
	void initialize();
	void update();
	void render();
	void release();
};