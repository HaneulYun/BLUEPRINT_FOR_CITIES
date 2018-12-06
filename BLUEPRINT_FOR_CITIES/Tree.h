#pragma once
#include "Object3d.h"

class Tree
{
	Object3d obj;
public:
	Tree();
	~Tree();
	void initialize();
	void update();
	void render();
	void release();
};
