#pragma once
#include "GameTime.h"
class tickClock
{
private:
	float maxTickTime;
	float currentTick;
	bool isClockEnabled;
public:
	tickClock(float maxTickTime) {
		this->maxTickTime = maxTickTime;
		this->currentTick = 0.f;
		this->isClockEnabled = true;
	}
	tickClock()
	{
		this->isClockEnabled = true;
		this->currentTick = 0.f;
		this->maxTickTime = 0.f;
	}
	bool isOnTick()
	{
		if (maxTickTime <= currentTick && isClockEnabled)
		{
			this->currentTick = 0.f;
			return true;
		}
		return false;
	}
	void enableClock() { this->isClockEnabled = true; }
	void disableClock() { this->isClockEnabled = false; }
	void setMaxTick(float maxTick) { this->maxTickTime = maxTick; }
	float getMaxTick() { return this->maxTickTime; }
	void update()
	{
		if (this->isClockEnabled)
			currentTick += GameTime::deltaTime;
	}

};