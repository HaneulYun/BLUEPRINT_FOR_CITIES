#pragma once
#include "ObjectUI.h"
#include "CheckBox.h"

class LowerBar
{
	ObjectUI obj;
	ObjectUI ch;
public:
	LowerBar();
	~LowerBar();
	void initialize();
	void update();
	void render();
	void release();

	int getChoose;
	void goNextLevel();

	CheckBox checkBox[7];
};