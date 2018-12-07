#include "TopBar.h"

TopBar::TopBar()
{
}

TopBar::~TopBar()
{
}

void TopBar::initialize()
{
	obj.setBMP("resources/menucolor.bmp");
	obj.setOBJ("resources/menubar.obj");
	obj.initialize();
	obj.setPosition(0, float(0.95), 0);
	obj.setColor(209.f / 255, 178.f / 255, 255.f / 255);
}

void TopBar::update()
{
	obj.update();
}

void TopBar::render()
{
	obj.render();
}

void TopBar::release()
{
	obj.release();
}