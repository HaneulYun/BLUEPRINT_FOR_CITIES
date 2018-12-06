#include <random>
#include <chrono>
#include "Tree.h"

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
	std::default_random_engine dre(std::chrono::steady_clock::now().time_since_epoch().count());

	obj.setBMP("resources/T_PolygonCity_Texture_01_A.bmp");
	switch (uid_7(dre)) {
	case 1: obj.setOBJ("resources/SM_Env_Tree_01_Internal.obj");	break;
	case 2: obj.setOBJ("resources/SM_Env_Tree_02_Internal.obj");	break;
	default: obj.setOBJ("resources/SM_Env_Tree_03_Internal.obj");	break;
	}
	obj.initialize();
	obj.setPosition(uid_200(dre) / 20.f, 0, uid_200(dre) / 20.f);
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