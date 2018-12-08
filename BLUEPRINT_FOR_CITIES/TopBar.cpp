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
	obj.setColor(43.f / 255, 63.f / 255, 74.f / 255);
	obj.setPosition(0, 550.0f, 0);
	obj.setScale(790.f, 450.f, 1.f);
}

void TopBar::update()
{
	obj.update();
	if (g_gameScene->viewMode)
		obj.setPosition(0, 550.f, 0);
	else
		obj.setPosition(0, 405.f, 0);
}

void TopBar::render()
{
	obj.render();
}

void TopBar::release()
{
	obj.release();
}