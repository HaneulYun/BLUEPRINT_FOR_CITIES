#include "SelectProp.h"
#include "GameScene.h"

SelectProp::SelectProp()
{
}

SelectProp::~SelectProp()
{
}

void SelectProp::initialize()
{
	mainobj.setBMP("resources/menucolor.bmp");
	mainobj.setOBJ("resources/SM_Env_Tree_02_Internal.obj");
	mainobj.initialize();
	mainobj.setColor(255.f / 255, 137.f / 255, 81.f / 255);
	mainobj.setScale(85.f, 85.f, 1.f);

	select = false;
}

void SelectProp::update()
{
	mainobj.update();
	if (g_gameScene->viewMode)
	{
		mainobj.setPosition(0, -1000, 0);
	}
	else
	{
		mainobj.setPosition(-450, -412, 0.1f);
	}
}

void SelectProp::render()
{
	if (!select) mainobj.render();
}

void SelectProp::release()
{
	mainobj.release();
}