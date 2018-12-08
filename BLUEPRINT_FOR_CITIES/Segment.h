#pragma once
#include "Object3d.h"
extern class Node;

class Segment
{
public:
	Object3d obj;
	Node* node1;
	Node* node2;
	Node* node3;

public:
	Segment();
	~Segment();
	void initialize();
	void update();
	void render();
	void release();
};

