#include "Player.h"

USING_NS_CC;

Player::Player(void)
{

}

Player::Player(int x, int y)
{
	Position.x = x;
	Position.y = y;
	timer = CatacombTimer(1);
}

void Player::turnLeft()
{
	int x = -Direction.x;
	int y = -Direction.y;
	Direction.x = Left.x;
	Direction.y = Left.y;
	Left.x = x;
	Left.y = y;
}

void Player::turnRight()
{
	int x = -Left.x;
	int y = -Left.y;
	Left.x = Direction.x;
	Left.y = Direction.y;
	Direction.x = x;
	Direction.y = y;
}

void Player::stepForward()
{
	if (canForward)
	{
		Position.x += Direction.x;
		Position.y += Direction.y;
	}
}

void Player::stepBackward()
{
	if (canBackward)
	{
		Position.x -= Direction.x;
		Position.y -= Direction.y;
	}
}
