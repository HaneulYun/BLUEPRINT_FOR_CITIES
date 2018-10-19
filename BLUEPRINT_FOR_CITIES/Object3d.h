#pragma once
#include <deque>
#include "Vector3.h"
#include "Object.h"

class Object3d : public Object
{
	unsigned char beginMode;
public:
	std::deque<Vector3> vectors;
public:
	Object3d();
	~Object3d();

	void initialize();
	void update();
	void render();
	void release();

	void setBeginMode(unsigned char mode);
	unsigned char getBeginMode() const;
};