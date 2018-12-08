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
	obj.setBMP("resources/menucolor.bmp");
	obj.setOBJ("resources/path.obj");
	obj.initialize();
	glm::vec3 position{ 0.f, 0, 0.f };
	position.y = g_gameScene->terrain->getHeightByPosition(position.x, position.z);
	obj.setPosition(position);
	obj.setScale(0.5f);
	for (auto& v : node)
		v = nullptr;
}

void Segment::update()
{
	obj.update();
}

void Segment::render()
{
	obj.render();
}

void Segment::release()
{
	obj.release();
}