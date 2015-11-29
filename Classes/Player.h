#ifndef __PLAYER_SCENE_H__
#define __PLAYER_SCENE_H__

#include "cocos2d.h"
#include "Vector2.h"
#include "CatacombTimer.h"

class Player
{
private:
	CatacombTimer timer;
public:
	// variables
	Vector2 Position;
	Vector2 Direction;
	Vector2 Left;
	float Battery;
	bool canForward = true;
	bool canBackward = false;

	// funciones
	Player();
	Player(int, int);
	void turnLeft();
	void turnRight();
	void stepForward();
	void stepBackward();
};

#endif