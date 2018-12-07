#include <Windows.h>
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
	oldTime = GetTickCount();
	delayTime = _delayTime;
}

bool Timer::isElapseTimer()
{
	unsigned long curTime = GetTickCount();
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