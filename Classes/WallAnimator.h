#ifndef __WALL_ANIMATOR_H__
#define __WALL_ANIMATOR_H__

#include "CatacombTimer.h"
#include "CentSprite.h"

using namespace std;

class WallAnimator
{
private:
	float fromX, fromY, fromW, fromH;
	float toX, toY, toW, toH;
	CentSprite* cs;

	bool changeOpacity = false;
	int initialOpacity;
    int finalOpacity;
public:
	WallAnimator(CentSprite*);
	void SetOrigin(float, float, float, float);
	void SetDestiny(float, float, float, float);
	void SetDestiny(float, float, float, float, int);
	void SetOrigin(float[4]);
	void SetDestiny(float[4]);
	void SetDestiny(float[4], int);

	void Animate(float);

};

#endif