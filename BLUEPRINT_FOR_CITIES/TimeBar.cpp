#include "TimeBar.h"
#include "GameScene.h"

TimeBar::TimeBar()
{
}

TimeBar::~TimeBar()
{
}

void TimeBar::initialize()
{
	obj.setBMP("resources/menucolor.bmp");
	obj.setOBJ("resources/topbar.obj");
	obj.initialize();
	obj.setPosition(0, 2.f, 0);
	obj.setColor(209.f / 255, 178.f / 255, 255.f / 255);
}

void TimeBar::update()
{
	obj.update();
	if (g_gameScene->viewMode)
		obj.setPosition(0, float(2.0), 0);
	else
		obj.setPosition(0, float(0.92), 0);
}

void TimeBar::render()
{
	obj.render();
}

void TimeBar::release()
{
	obj.release();
}