#pragma once
#include <glm/glm.hpp>
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

	glm::vec3 getPosition() const { return obj.getPosition(); }
};