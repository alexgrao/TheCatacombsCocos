#ifndef __CATACOMB_TIMER_H__
#define __CATACOMB_TIMER_H__

class CatacombTimer
{
private:
	float interval;
	float currentTime = 0;
	float percentage = 0;
	int counter = 0;
	bool running = true;

public:
	CatacombTimer();
	CatacombTimer(float);
	void Start();
	void Stop();
	void Reset();
	void Restart();

	float GetCurrentTime();
	float GetInterval();
	void SetInterval(float);
	float GetPercentageFull();
	int GetCount();

	bool Check(float);
};

#endif