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
	frame.setColor(222.f / 255, 215.f / 255, 71.f / 255);
	frame.setPosition(0.f, 0.f, -1.f);
	frame.setScale(10.f,10.f,1.f);

	bar.setBMP("resources/menucolor.bmp");
	bar.setOBJ("resources/daybar.obj");
	bar.initialize();
	bar.setColor(222.f / 255, 215.f / 255, 71.f / 255);
	bar.setPosition(0.f, 0.f, -1.f);
	//bar.setScale(0.07f, 0.14f, 1.0f);
}

void TimeBar::update()
{
	frame.update();
	bar.update();
	//if (g_gameScene->viewMode)
	//{
	//	frame.setPosition(0, float(2.0), 0);
	//	bar.setPosition(0, float(2.0), 0);
	//}
	//else
	//{
	//	frame.setPosition(-0.9, 0.92f, -0.1f);
	//	bar.setPosition(-0.9, 0.92f, -0.1f);
	//}
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