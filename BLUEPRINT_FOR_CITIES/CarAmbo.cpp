#include <random>
#include <chrono>
#include "CarAmbo.h"
#include "GameScene.h"

CarAmbo::CarAmbo()
{
}

CarAmbo::~CarAmbo()
{
}

void CarAmbo::initialize()
{
	std::uniform_int_distribution<int> uid_7(0, 6);
	std::uniform_int_distribution<int> uid_360(1, 360);
	std::uniform_int_distribution<int> uid_200(-100, 100);
	std::uniform_int_distribution<int> uid_400(-200, 199);
	std::default_random_engine dre(std::chrono::steady_clock::now().time_since_epoch().count());

	obj.setBMP("resources/T_PolygonCity_Texture_01_A.bmp");
	switch (uid_7(dre)) {
	case 1: obj.setOBJ("resources/carAmbo.obj");	break;
	case 2: obj.setOBJ("resources/muscle.obj");	break;
	case 3: obj.setOBJ("resources/small.obj");	break;
	default: obj.setOBJ("resources/van.obj");	break;
	}
	obj.initialize();
	glm::vec3 position{ uid_400(dre) / 20.f, 0, uid_400(dre) / 20.f };
	position.y = g_gameScene->terrain->getHeightByPosition(position.x, position.z) + 0.15f;
	obj.setPosition(position);
	obj.setRotation(0, float(uid_360(dre)), 0);
	obj.setScale(0.5f);
}

void CarAmbo::update()
{
	obj.update();
}

void CarAmbo::render()
{
	obj.render();
}

void CarAmbo::release()
{
	obj.release();
}

void CarAmbo::extractDepthmap()
{
	obj.extractDepthmap();
}