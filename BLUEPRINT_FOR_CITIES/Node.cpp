#include <random>
#include <chrono>
#include "Node.h"
#include "Segment.h"
#include "GameScene.h"

Node::Node()
{
}

Node::~Node()
{
}

void Node::initialize()
{
	obj.setBMP("resources/menucolor.bmp");
	obj.setOBJ("resources/path.obj");
	obj.initialize();
	glm::vec3 position{ 0.f, 0, 0.f };
	position.y = g_gameScene->terrain->getHeightByPosition(position.x, position.z);
	obj.setPosition(position);
	obj.setScale(0.2f);
}

void Node::update()
{
	obj.update();
}

void Node::render()
{
	obj.render();
}

void Node::release()
{
	obj.release();
}