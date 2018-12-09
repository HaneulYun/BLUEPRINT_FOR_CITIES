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

	subS.setBMP("resources/menucolor.bmp");
	subS.setOBJ("resources/roadimg.obj");
	subS.initialize();
	subS.setColor(255.f / 255, 137.f / 255, 81.f / 255);
	subS.setScale(40.f, 40.f, 1.f);

	subC.setBMP("resources/menucolor.bmp");
	subC.setOBJ("resources/roadcimg.obj");
	subC.initialize();
	subC.setColor(255.f / 255, 137.f / 255, 81.f / 255);
	subC.setScale(40.f, 40.f, 1.f);

	select = false;
}

void SelectRoad::update()
{
	mainobj.update();
	subS.update();
	subC.update();
	if (g_gameScene->viewMode)
	{
		mainobj.setPosition(0, -1000, 0);
		subS.setPosition(0, -1000, 0);
		subC.setPosition(0, -1000, 0);
	}
	else
	{
		mainobj.setPosition(-650, -370, 0.1f);
		subS.setPosition(-650, -370, 0.1f);
		subC.setPosition(-450, -370, 0.1f);
	}
}

void SelectRoad::render()
{
	if (!select && !g_gameScene->selectProp.select && !g_gameScene->selectGrid.select) mainobj.render();
	else if (select)
	{
		subS.render();
		subC.render();
	}
}

void SelectRoad::release()
{
	mainobj.release();
	subS.release();
	subC.release();
}