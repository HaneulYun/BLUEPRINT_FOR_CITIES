#pragma once
#include "ObjectLight.h"

class Sun
{
	ObjectLight obj;
	float radianPosition{ 0 };

public:
	Sun();
	~Sun();

	void initialize();
	void update();
	void render();
	void release();

	bool pause;
	float sunclock;
	float getRadianPosition() const;
	glm::vec3 getLightPos() const;
};

