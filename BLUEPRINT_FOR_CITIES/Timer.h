#pragma once

class Timer
{
public:
	unsigned long oldTime;
	unsigned long delayTime;
public:
	Timer(void);
	virtual ~Timer(void);

	void initTimer(unsigned long dwDelayTime);
	bool isElapseTimer();
	bool isValidTimer();
};