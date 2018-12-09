#include <algorithm>
#include <random>
#include "Sun.h"
#include "GameScene.h"

Sun::Sun()
{
}

Sun::~Sun()
{
}

void Sun::initialize()
{
	radianPosition = 0.f;
	sunclock = 0.005f;
	pause = false;
}

void Sun::update()
{
	if (!pause)
		radianPosition += sunclock;
	static std::uniform_int_distribution<int> uid(0, 1);
	static std::default_random_engine dre;
	auto& v = g_gameScene->propManager.streetLight;
	if (radianPosition >= 2 * 3.141592f)
	{
		radianPosition = 0.0;
		for (int i = 0; i < v.size() - 1; ++i)
		{
			for (int j = i; j < v.size(); ++j)
			{
				if (uid(dre))
				{
					StreetLight* t = v[i];
					v[i] = v[j];
					v[j] = t;
				}
			}
		}
	}
}

void Sun::render()
{

}

void Sun::release()
{

}

float Sun::getRadianPosition() const
{
	return radianPosition;
}

glm::vec3 Sun::getLightPos() const
{
	return glm::vec3(20 * cos(radianPosition), 20 * sin(radianPosition), 0);
}