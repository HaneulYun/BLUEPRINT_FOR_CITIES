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