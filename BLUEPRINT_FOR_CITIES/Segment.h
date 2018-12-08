#pragma once
#include "Object3d.h"
extern class Node;

class Segment
{
public:
	Object3d obj;
	Node* node[3];

public:
	Segment();
	~Segment();
	void initialize();
	void update();
	void render();
	void release();
};

