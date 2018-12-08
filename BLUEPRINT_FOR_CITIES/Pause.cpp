#include "Pause.h"
#include "GameScene.h"

Pause::Pause()
{
}

Pause::~Pause()
{
}

void Pause::initialize()
{
	obj.setBMP("resources/menucolor.bmp");
	obj.setOBJ("resources/pause.obj");
	obj.initialize();
	obj.setColor(255.f / 255, 137.f / 255, 81.f / 255);
	obj.setScale(20.f, 20.f, 1.f);
}

void Pause::update()
{
	obj.update();
	if (g_gameScene->viewMode)
	{
		obj.setPosition(0, -550, 0);
	}
	else
	{
		obj.setPosition(-520, 405, 0.1f);
	}
}

void Pause::render()
{
	if (g_gameScene->sun.pause)
		obj.render();
}

void Pause::release()
{
	obj.release();
}