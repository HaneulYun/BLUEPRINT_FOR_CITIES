#include "Sun.h"

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
}

void Sun::update()
{
	radianPosition += sunclock;
	if (radianPosition >= 2 * 3.141592f)
	{
		radianPosition = 0.0;
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