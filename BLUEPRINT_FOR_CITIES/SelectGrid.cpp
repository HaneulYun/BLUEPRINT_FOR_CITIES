#include "SelectGrid.h"
#include "GameScene.h"

SelectGrid::SelectGrid()
{
}

SelectGrid::~SelectGrid()
{
}

void SelectGrid::initialize()
{
	mainobj.setBMP("resources/menucolor.bmp");
	mainobj.setOBJ("resources/gridimg.obj");
	mainobj.initialize();
	mainobj.setColor(255.f / 255, 137.f / 255, 81.f / 255);
	mainobj.setScale(38.f, 38.f, 1.f);

	select = false;
}

void SelectGrid::update()
{
	mainobj.update();
	if (g_gameScene->viewMode)
	{
		mainobj.setPosition(0, -1000, 0);
	}
	else
	{
		mainobj.setPosition(-250, -370, 0.1f);
	}
}

void SelectGrid::render()
{
	mainobj.render();
}

void SelectGrid::release()
{
	mainobj.release();
}