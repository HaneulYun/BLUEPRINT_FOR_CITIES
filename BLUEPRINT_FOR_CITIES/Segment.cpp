#include <random>
#include <chrono>
#include "Segment.h"
#include "Node.h"
#include "GameScene.h"

Segment::Segment()
{
}

Segment::~Segment()
{
}

void Segment::initialize()
{
	obj.setBMP("resources/T_PolygonCity_Texture_01_A.bmp");
	obj.setOBJ("resources/SM_Prop_LargeSign_Burger_01_Internal.obj");
	obj.initialize();
	glm::vec3 position{ 0.f, 0, 0.f };
	position.y = g_gameScene->terrain->getHeightByPosition(position.x, position.z);
	obj.setPosition(position);
	obj.setScale(0.5f);
}

void Segment::update()
{
	obj.update();
	if (g_gameScene->straight)//�����׸����� �׷�����
	{

	}
	else if (!g_gameScene->straight)//��׸����� �׷�����
	{

	}
}

void Segment::render()
{
	obj.render();
}

void Segment::release()
{
	obj.release();
}