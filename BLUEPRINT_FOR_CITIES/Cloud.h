#pragma once
#include "Object3d.h"

class Cloud
{
	float oriScale;
	float elapsedTime;
public:
	Object3d obj;
	Cloud();
	~Cloud();
	void initialize();
	void update();
	void render();
	void release();
	void extractDepthmap();
};