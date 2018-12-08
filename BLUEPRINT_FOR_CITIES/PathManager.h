#pragma once
#include "Node.h"
#include "Segment.h"

class PathManager
{
	std::list<Node*> node;
	std::list<Segment*> segment;

public:
	PathManager();
	~PathManager();

	void initialize();
	void update();
	void render();
	void release();
};

