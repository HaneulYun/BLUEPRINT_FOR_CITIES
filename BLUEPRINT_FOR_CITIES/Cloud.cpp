#include <random>
#include <chrono>
#include "Cloud.h"
#include "GameScene.h"

Cloud::Cloud()
{
}

Cloud::~Cloud()
{
}

void Cloud::initialize()
{
	std::uniform_int_distribution<int> uid_10(1, 10);
	std::uniform_int_distribution<int> uid_400(-200, 199);
	std::default_random_engine dre(std::chrono::steady_clock::now().time_since_epoch().count());

	obj.setBMP("resources/T_PolygonCity_Texture_01_A.bmp");
	obj.setOBJ("resources/SM_Env_Cloud_01_Internal.obj");
	obj.initialize();

	glm::vec3 position{ uid_400(dre) / 20.f, 5.f, uid_400(dre) / 20.f };
	obj.setPosition(position);
	//obj.setRotation(0, float(uid_10(dre)), 0);
	oriScale = 1 + uid_10(dre) / 5.f;
	elapsedTime = uid_10(dre) / 5.f * 3.141592;
}

void Cloud::update()
{
	elapsedTime += 0.01;
	obj.setScale(oriScale + 0.2 * sin(elapsedTime));
	obj.update();
}

void Cloud::render()
{
	obj.render();
}

void Cloud::release()
{
	obj.release();
}