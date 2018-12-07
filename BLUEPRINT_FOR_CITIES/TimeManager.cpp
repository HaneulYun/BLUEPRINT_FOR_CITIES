#include <Windows.h>
#include <time.h>
#include "TimeManager.h"

TimeManager::TimeManager(void)
{
	acculTime = 0.0f;	// 누적시간
	fps = 0.0f;			// FPS
	timeStep = 0.0f;		// 현재시간.
	fpsTime = 0.0f;

	nFrameCount = 0;
	beforeTime = 0;

	//timeBeginPeriod(1);
}

TimeManager::~TimeManager(void)
{
	release();
}

bool TimeManager::initialize()
{
	beforeTime = GetTickCount();

	return true;
}

void TimeManager::release()
{
	//timeEndPeriod(1);
}

void TimeManager::update()
{
	unsigned long time = GetTickCount();

	unsigned long tick = time - beforeTime;
	timeStep = (float)tick * 0.001f;
	acculTime += timeStep;

	fpsTime += timeStep;
	if (fpsTime > 1.0f)
	{
		fps = (float)nFrameCount / fpsTime;
		fpsTime = 0.0f;
		nFrameCount = 0;
	}
	else
	{
		nFrameCount++;
	}
	beforeTime = time;
}
