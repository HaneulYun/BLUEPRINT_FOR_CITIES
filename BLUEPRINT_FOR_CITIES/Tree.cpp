#include <random>
#include <chrono>
#include "Tree.h"
#include "GameScene.h"

Tree::Tree()
{
}

Tree::~Tree()
{
}

void Tree::initialize()
{
	std::uniform_int_distribution<int> uid_7(0, 6);
	std::uniform_int_distribution<int> uid_360(1, 360);
	std::uniform_int_distribution<int> uid_200(-100, 100);
	std::uniform_int_distribution<int> uid_400(-200, 200);
	std::default_random_engine dre(std::chrono::steady_clock::now().time_since_epoch().count());

	obj.setBMP("resources/T_PolygonCity_Texture_01_A.bmp");
	switch (uid_7(dre)) {
	case 1: obj.setOBJ("resources/SM_Env_Tree_01_Internal.obj");	break;
	case 2: obj.setOBJ("resources/SM_Env_Tree_02_Internal.obj");	break;
	default: obj.setOBJ("resources/SM_Env_Tree_03_Internal.obj");	break;
	}
	obj.initialize();
	glm::vec3 position{ uid_400(dre) / 20.f, 0, uid_400(dre) / 20.f };
	position.y = g_gameScene->terrain.heights[int((position.z + 10) * 3)][int((position.x + 10) * 3)];
	obj.setPosition(position);
	obj.setRotation(0, float(uid_360(dre)), 0);
	obj.setScale(1 + float(uid_200(dre) / 200.f));
}

void Tree::update()
{
	obj.update();
}

void Tree::render()
{
	obj.render();
}

void Tree::release()
{
	obj.release();
}