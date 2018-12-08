#pragma once
#include "Cloud.h"
#include "StreetLight.h"
#include "Tree.h"

enum Choose {TREE, CLOUD, STREETLIGHT };

class PropManager
{
public:
	std::list<Tree*> tree;
	std::list<StreetLight*> streetLight;
	std::list<Cloud*> cloud;
	bool drawState{ false };
	Choose chooseProp;

public:
	PropManager();
	~PropManager();

	void initialize();
	void update();
	void render();
	void release();

	void inputInitialize();
	void inputProp(Choose prop);
};

