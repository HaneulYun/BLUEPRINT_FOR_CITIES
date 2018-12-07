#include "TopBar.h"
#include "GameScene.h"

TopBar::TopBar()
{
}

TopBar::~TopBar()
{
}

void TopBar::initialize()
{
	obj.setBMP("resources/menucolor.bmp");
	obj.setOBJ("resources/topbar.obj");
	obj.initialize();
	obj.setPosition(0, 2.f, 0);
	obj.setColor(43.f / 255, 63.f / 255, 74.f / 255);
}

void TopBar::update()
{
	obj.update();
	if (g_gameScene->viewMode)
		obj.setPosition(0, float(2.0), 0);
	else
		obj.setPosition(0, float(0.92), 0);
}

void TopBar::render()
{
	obj.render();
}

void TopBar::release()
{
	obj.release();
}