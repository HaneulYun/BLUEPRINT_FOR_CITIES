#include <random>
#include <chrono>
#include "StreetLight.h"
#include "GameScene.h"

StreetLight::StreetLight()
{
}

StreetLight::~StreetLight()
{
}

void StreetLight::initialize()
{
	std::uniform_int_distribution<int> uid_360(1, 360);
	std::uniform_int_distribution<int> uid_400(-200, 199);
	std::default_random_engine dre(std::chrono::steady_clock::now().time_since_epoch().count());

	obj.setBMP("resources/T_PolygonCity_Texture_01_A.bmp");
	obj.setOBJ("resources/SM_Prop_LightPole_Base_02_Internal.obj");
	obj.initialize();
	glm::vec3 position{ uid_400(dre) / 20.f, 0, uid_400(dre) / 20.f };
	position.y = g_gameScene->terrain->getHeightByPosition(position.x, position.z);
	obj.setPosition(position);
	obj.setRotation(0, float(uid_360(dre)), 0);
	obj.setScale(0.5f);
}

void StreetLight::update()
{
	obj.update();
}

void StreetLight::render()
{
	obj.render();
}

void StreetLight::release()
{
	obj.release();
}

void StreetLight::extractDepthmap()
{
	obj.extractDepthmap();
}