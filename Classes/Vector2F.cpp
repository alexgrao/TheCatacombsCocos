#include "Vector2F.h"

USING_NS_CC;

Vector2F::Vector2F(void)
{
	x = 0;
	y = 0;
}

Vector2F::Vector2F(float x_, float y_)
{
	x = x_;
	y = y_;
}

Vector2F Vector2F::Copy()
{
	return Vector2F(x, y);
}