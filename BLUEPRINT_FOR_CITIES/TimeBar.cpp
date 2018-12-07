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
	frame.setBMP("resources/menucolor.bmp");
	frame.setOBJ("resources/dayframe.obj");
	frame.initialize();
	frame.setPosition(-0.9, 0.92f, -0.1f);
	frame.setColor(222.f / 255, 215.f / 255, 71.f / 255);
	frame.setScale(0.08f,0.15f,1.0f);
	bar.setBMP("resources/menucolor.bmp");
	bar.setOBJ("resources/daybar.obj");
	bar.initialize();
	bar.setPosition(-0.9, 0.92f, -0.1f);
	bar.setColor(222.f / 255, 215.f / 255, 71.f / 255);
	bar.setScale(0.07f, 0.14f, 1.0f);
}

void TimeBar::update()
{
	frame.update();
	bar.update();
	if (g_gameScene->viewMode)
	{
		frame.setPosition(0, float(2.0), 0);
		bar.setPosition(0, float(2.0), 0);
	}
	else
	{
		frame.setPosition(-0.9, 0.92f, -0.1f);
		bar.setPosition(-0.9, 0.92f, -0.1f);
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