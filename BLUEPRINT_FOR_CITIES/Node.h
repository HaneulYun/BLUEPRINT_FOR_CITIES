#pragma once
#include "Object3d.h"
extern class Segment;

class Node
{
	std::vector<Segment*> segment;

public:
	Object3d obj;

public:
	Node();
	~Node();
	void initialize();
	void update();
	void render();
	void release();
};