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

	ch.setBMP("resources/menucolor.bmp");
	ch.setOBJ("resources/chimg.obj");
	ch.initialize();
	ch.setColor(255.f / 255, 137.f / 255, 81.f / 255);
	ch.setScale(10.f, 10.f, 1.f);

	for (int i = 0; i < 7; ++i)
	{
		checkBox[i].x = -650 + i * 200;
		checkBox[i].y = -400.0;
	}
}

void LowerBar::update()
{
	obj.update();
	ch.update();
	if (g_gameScene->viewMode)
	{
		obj.setPosition(0, -550, 0);
		ch.setPosition(0, -550, 0);
	}
	else
	{
		obj.setPosition(0, -365, 0);
		ch.setPosition(-650 + getChoose * 200, -300, 0.1f);
	}
}

void LowerBar::render()
{
	obj.render();
	ch.render();
}

void LowerBar::goNextLevel()
{
	if (g_gameScene->selectGrid.select == false && g_gameScene->selectProp.select == false && g_gameScene->selectRoad.select == false)
	{
		switch (getChoose)
		{
		case 0:
			g_gameScene->selectRoad.select = true;
			g_gameScene->pathManager.drawRoadState = true;
			break;
		case 1:
			g_gameScene->selectProp.select = true;
			g_gameScene->propManager.drawPropState = true;
			break;
		case 2:
			g_gameScene->selectGrid.select = true;
			break;
		}
	}
	else if (g_gameScene->selectRoad.select == true)
	{
		switch (getChoose)
		{
		case 0:
			g_gameScene->pathManager.drawMode = false;
			break;
		case 1:
			g_gameScene->pathManager.drawMode = true;
			break;
		}
	}
	else if (g_gameScene->selectProp.select == true)
	{
		switch (getChoose)
		{
		case 0:
			g_gameScene->propManager.chooseProp = TREE;
			break;
		case 1:
			g_gameScene->propManager.chooseProp = CLOUD;
			break;
		case 2:
			g_gameScene->propManager.chooseProp = STREETLIGHT;
			break;
		case 3:
			g_gameScene->propManager.chooseProp = MAILBOX;
			break;
		case 4:
			g_gameScene->propManager.chooseProp = HYDRANT;
			break;
		case 5:
			g_gameScene->propManager.chooseProp = CONE;
			break;
		}
	}
	else if (g_gameScene->selectGrid.select == true)
	{

	}
}

void LowerBar::release()
{
	obj.release();
	ch.release();
}