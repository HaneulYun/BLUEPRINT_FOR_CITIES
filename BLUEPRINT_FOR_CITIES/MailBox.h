#pragma once
#include "Object3d.h"

class MailBox
{

public:
	Object3d obj;
	MailBox();
	~MailBox();
	void initialize();
	void update();
	void render();
	void release();
	void extractDepthmap();
};

