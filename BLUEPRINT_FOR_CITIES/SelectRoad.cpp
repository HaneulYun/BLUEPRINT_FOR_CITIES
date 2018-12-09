#include "SelectRoad.h"
#include "GameScene.h"

SelectRoad::SelectRoad()
{
}

SelectRoad::~SelectRoad()
{
}

void SelectRoad::initialize()
{
	mainobj.setBMP("resources/menucolor.bmp");
	mainobj.setOBJ("resources/roadimg.obj");
	mainobj.initialize();
	mainobj.setColor(255.f / 255, 137.f / 255, 81.f / 255);
	mainobj.setScale(40.f, 40.f, 1.f);

	select = false;
}

void SelectRoad::update()
{
	mainobj.update();
	if (g_gameScene->viewMode)
	{
		mainobj.setPosition(0, -1000, 0);
	}
	else
	{
		mainobj.setPosition(-650, -370, 0.1f);
	}
}

void SelectRoad::render()
{
	mainobj.render();
}

void SelectRoad::release()
{
	mainobj.release();
}