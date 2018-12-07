#pragma once
#include "ObjectUI.h"

class TopBar
{
	ObjectUI obj;
public:
	TopBar();
	~TopBar();
	void initialize();
	void update();
	void render();
	void release();
};