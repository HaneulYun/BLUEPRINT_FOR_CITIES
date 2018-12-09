#include "DestroyEffect.h"
#include "GameScene.h"
#define PI 3.141592

DestroyEffect::DestroyEffect()
{
}

DestroyEffect::~DestroyEffect()
{
}

void DestroyEffect::initialize()
{
	frame.setBMP("resources/menucolor.bmp");
	frame.setOBJ("resources/destroyframe.obj");
	frame.initialize();
	frame.setColor(231.f / 25, 205.f / 255, 103.f / 255);
	frame.setScale(800.f, 800.f, 1.f);

	ppip.setBMP("resources/menucolor.bmp");
	ppip.setOBJ("resources/destroyppip.obj");
	ppip.initialize();
	ppip.setColor(61.f / 255, 50.f / 255, 10.f / 255);
	ppip.setScale(800.f, 800.f, 1.f);
}

void DestroyEffect::update()
{
	frame.update();
	ppip.update();
	if (g_gameScene->destroyMode)
	{
		frame.setPosition(0, 0.f, 0.2f);
		ppip.setPosition(0, 0.f, 0.3f);
	}
	else
	{
		frame.setPosition(0, 1000.f, 0);
		ppip.setPosition(0, 1000.f, 0);
	}
}

void DestroyEffect::render()
{
	frame.render();
	ppip.render();
}

void DestroyEffect::release()
{
	frame.release();
	ppip.release();
}