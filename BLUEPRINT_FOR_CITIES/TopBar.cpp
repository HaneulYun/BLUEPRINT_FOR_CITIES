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
	obj.setOBJ("resources/topbar.obj");
	obj.initialize();
	obj.setPosition(0, float(0.95), 0);
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