#pragma once
#include "Object3d.h"

class Cone
{

public:
	Object3d obj;
	Cone();
	~Cone();
	void initialize();
	void update();
	void render();
	void release();
	void extractDepthmap();
};

