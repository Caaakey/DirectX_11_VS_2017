#pragma once

class Timer
{
public:
	Timer();
	static Timer* Get() {
		static Timer Instance;
		return &Instance;
	}

	void UpdateTime(float frameLock = 60.0f);

	inline float GetWorldTime(void) const { return worldTime; }
	inline float GetFPSTime(void) { return (float)frameRate; }
	inline float GetElapsedTime(void) const { return timeElapsed; }

private:
	bool isHardware;

	float timeScale;
	float timeElapsed;
	__int64 preriodTime;
	__int64 lastTime;
	__int64 currTime;

	unsigned long frameRate;
	unsigned long fpsFrameCount;

	float fpsTimeElapsed;
	float worldTime;
};
#define _Timer Timer::Get()