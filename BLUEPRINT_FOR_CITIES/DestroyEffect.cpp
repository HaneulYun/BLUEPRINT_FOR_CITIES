#include "DestroyEffect.h"
#include "GameScene.h"

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
	frame.setColor(234.f / 255, 223.f / 255, 94.f / 255);
	frame.setScale(100.f, 100.f, 1.f);

	ppip.setBMP("resources/menucolor.bmp");
	ppip.setOBJ("resources/destroyppip.obj");
	ppip.initialize();
	ppip.setColor(64.f / 255, 60.f / 255, 9.f / 255);
	ppip.setScale(800.f, 800.f, 1.f);
}

void DestroyEffect::update()
{
	frame.update();
	ppip.update();
	if (g_gameScene->viewMode)
	{
		frame.setPosition(0, -900, 0);
		ppip.setPosition(0, -900, 0);
	}
	else
	{
		frame.setPosition(0, 0, 0.2f);
		ppip.setPosition(0, 0, 0.3f);
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