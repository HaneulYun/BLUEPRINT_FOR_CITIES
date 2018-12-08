#pragma once
#include "Node.h"
#include "Segment.h"

enum E_DRAW_MODE{ STRAIGHT, CURVE, DRAW_MAX_CNT };

class PathManager
{
	Segment builder;

	std::list<Node*> node;
	std::list<Segment*> segment;

public:
	bool drawState{ false };
	bool drawMode{ false };	// E_DRAW_MODE

public:
	PathManager();
	~PathManager();

	void initialize();
	void update();
	void render();
	void release();

	void inputInitialize();
	void inputNode(Node* _node);
};

