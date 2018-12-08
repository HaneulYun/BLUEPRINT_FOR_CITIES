#include "TimeBar.h"
#include "GameScene.h"
#define PI 3.141592

TimeBar::TimeBar()
{
}

TimeBar::~TimeBar()
{
}

void TimeBar::initialize()
{
	frame.setBMP("resources/menucolor.bmp");
	frame.setOBJ("resources/dayframe.obj");
	frame.initialize();
	frame.setColor(255.f / 255, 137.f / 255, 81.f / 255);
	frame.setScale(50.f, 50.f, 1.f);

	bar.setBMP("resources/menucolor.bmp");
	bar.setOBJ("resources/daybar.obj");
	bar.initialize();
	bar.setColor(255.f / 255, 137.f / 255, 81.f / 255);
	bar.setScale(45.f, 45.f, 1.f);
}

void TimeBar::update()
{
	frame.update();
	bar.update();
	bar.setScale(45.f * Object::radian / 2 / PI, 45.f, 1.f);
	if (g_gameScene->viewMode)
	{
		frame.setPosition(0, 500.f, 0);
		bar.setPosition(0, 500.f, 0);
	}
	else
	{
		frame.setPosition(-720, 405.f, 1.0f);
		bar.setPosition(-765 + 45 * Object::radian / 2 / PI, 405.f, 1.0f);
	}
}

void TimeBar::render()
{
	frame.render();
	bar.render();
}

void TimeBar::release()
{
	frame.release();
	bar.release();
}