#pragma once
#include "ObjectUI.h"

class SelectProp
{
	ObjectUI mainobj;

	ObjectUI subTree;
	ObjectUI subCloud;
	ObjectUI subStreetlight;
	ObjectUI subMailbox;
	ObjectUI subHydrant;
	ObjectUI subCone;

public:
	SelectProp();
	~SelectProp();
	void initialize();
	void update();
	void render();
	void release();

	bool select;
};