#include "LowerBar.h"
#include "GameScene.h"

LowerBar::LowerBar()
{
}

LowerBar::~LowerBar()
{
}

void LowerBar::initialize()
{
	obj.setBMP("resources/menucolor.bmp");
	obj.setOBJ("resources/lowerbar.obj");
	obj.initialize();
	obj.setPosition(0, -float(2.0), 0);
}

void LowerBar::update()
{
	obj.update();
	if (g_gameScene->viewMode)
		obj.setPosition(0, -float(2.0), 0);
	else
		obj.setPosition(0, -float(0.82), 0);
}

void LowerBar::render()
{
	obj.render();
}

void LowerBar::release()
{
	obj.release();
}