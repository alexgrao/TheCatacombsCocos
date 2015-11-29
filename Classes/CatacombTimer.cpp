#include "CatacombTimer.h"

CatacombTimer::CatacombTimer() { interval = 1; }

CatacombTimer::CatacombTimer(float Interval) { interval = Interval; }

bool CatacombTimer::Check(float delta)
{
	if (running)
	{
		currentTime += delta;
		bool toReturn = false;

		if (currentTime >= interval)
		{
			++counter;
			currentTime = currentTime - interval;
			toReturn = true;
		}

		percentage = currentTime / interval;

		return toReturn;
	}
	else return false;
}

void CatacombTimer::Start() { running = true;}

void CatacombTimer::Stop() { running = false; }

void CatacombTimer::Reset()
{
	currentTime = 0;
	running = false;
	counter = 0;
}

void CatacombTimer::Restart()
{
	currentTime = 0;
	running = true;
}

float CatacombTimer::GetTime() { return currentTime; }

float CatacombTimer::GetInterval() { return interval; }

void CatacombTimer::SetInterval(float Interval) { interval = Interval; }

float CatacombTimer::GetPercentageFull() { return percentage; }

int CatacombTimer::GetCount() { return counter; }