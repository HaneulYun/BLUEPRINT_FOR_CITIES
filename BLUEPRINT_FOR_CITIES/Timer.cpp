#include <glfw3.h>
#include <time.h>
#include "Timer.h"

Timer::Timer(void)
{
}

Timer::~Timer(void)
{
}

void Timer::initTimer(unsigned long _delayTime)
{
	oldTime = glfwGetTime();
	delayTime = _delayTime;
}

bool Timer::isElapseTimer()
{
	unsigned long curTime = glfwGetTime();
	unsigned long elapsed = curTime - oldTime;

	if (elapsed >= delayTime)
	{
		delayTime = 0;
		oldTime = curTime;
		return true;
	}

	return false;
}

bool Timer::isValidTimer()
{
	if (delayTime)
		return true;
	else
		return false;
}