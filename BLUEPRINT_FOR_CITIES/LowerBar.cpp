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
	obj.setPosition(0, -550, 0);
	obj.setColor(43.f / 255, 63.f / 255, 74.f / 255);
	obj.setScale(790.f, 450.f, 1.f);
}

void LowerBar::update()
{
	obj.update();
	if (g_gameScene->viewMode)
		obj.setPosition(0, -550, 0);
	else
		obj.setPosition(0, -365, 0);
}

void LowerBar::render()
{
	obj.render();
}

void LowerBar::release()
{
	obj.release();
}