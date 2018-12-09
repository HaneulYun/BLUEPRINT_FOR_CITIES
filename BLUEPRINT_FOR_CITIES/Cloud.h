#pragma once
#include "Object3d.h"

class Cloud
{
	Object3d obj;
	float oriScale;
	float elapsedTime;
public:
	Cloud();
	~Cloud();
	void initialize();
	void update();
	void render();
	void release();
	void extractDepthmap();
};