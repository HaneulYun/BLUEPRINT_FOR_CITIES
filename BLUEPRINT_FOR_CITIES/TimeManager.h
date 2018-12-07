#pragma once

class TimeManager
{
public:
	float acculTime;
	float fps;
	float timeStep;
	float fpsTime;

	int nFrameCount;
	unsigned long beforeTime;

public:
	TimeManager(void);
	virtual ~TimeManager(void);

	bool initialize();
	void release();
	void update();

public:
	__inline float getTime() const;
	__inline float getFPS() const;
	__inline float getTimeStep() const;
};

__inline float TimeManager::getTime() const
{
	return acculTime;;
}

__inline float TimeManager::getFPS() const
{
	return fps;
}
__inline float TimeManager::getTimeStep() const
{
	return timeStep;
}