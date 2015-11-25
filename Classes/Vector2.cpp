#include "Vector2.h"

USING_NS_CC;

Vector2::Vector2(void)
{
	x = 0;
	y = 0;
}

Vector2::Vector2(int x_, int y_)
{
	x = x_;
	y = y_;
}

Vector2 Vector2::Copy()
{
	return Vector2(x, y);
}