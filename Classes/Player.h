#ifndef __PLAYER_SCENE_H__
#define __PLAYER_SCENE_H__

using namespace std;

#include "cocos2d.h"
#include "Vector2.h"

class Player
{
public:
	// variables
	Vector2 Position;
	Vector2 Direction;
	Vector2 Left;
	float Battery;
	bool canForward;
	bool canBackward;

	// funciones
	Player();
	Player(int, int);
	void turnLeft();
	void turnRight();
	void stepForward();
	void stepBackward();
};

#endif