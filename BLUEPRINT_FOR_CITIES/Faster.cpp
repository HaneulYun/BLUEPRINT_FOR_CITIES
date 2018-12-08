#include "Faster.h"
#include "GameScene.h"

Faster::Faster()
{
}

Faster::~Faster()
{
}

void Faster::initialize()
{
	obj.setBMP("resources/menucolor.bmp");
	obj.setOBJ("resources/fasterfull.obj");
	obj.initialize();
	obj.setColor(255.f / 255, 137.f / 255, 81.f / 255);
	obj.setScale(30.f, 30.f, 1.f);

	faster = false;
}

void Faster::update()
{
	obj.update();
	if (g_gameScene->viewMode)
	{
		obj.setPosition(0, -550, 0);
	}
	else
	{
		obj.setPosition(-600, 405, 0.1f);
	}
}

void Faster::render()
{
	if (faster)
		obj.render();
}

void Faster::release()
{
	obj.release();
}