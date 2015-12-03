#include "WallAnimator.h"

WallAnimator::WallAnimator(CentSprite* CS)
{
	cs = CS;

	fromX = 0;
	fromY = 0;
	fromW = 0;
	fromH = 0;

	toX = 0;
	toY = 0;
	toW = 0;
	toH = 0;
}

void WallAnimator::SetOrigin(float x, float y, float width, float height)
{
	fromX = x;
	fromY = y;
	fromW = width;
	fromH = height;
}

void WallAnimator::SetDestiny(float x, float y, float width, float height)
{
	toX = x;
	toY = y;
	toW = width;
	toH = height;
}

void WallAnimator::SetDestiny(float x, float y, float width, float height, int opacity)
{
	toX = x;
	toY = y;
	toW = width;
	toH = height;
	changeOpacity = true;
	initialOpacity = cs->sprite->getOpacity();
	finalOpacity = opacity;
}

void WallAnimator::SetOrigin(float params[4])
{
	fromX = params[0];
	fromY = params[1];
	fromW = params[2];
	fromH = params[3];
}

void WallAnimator::SetDestiny(float params[4])
{
	toX = params[0];
	toY = params[1];
	toW = params[2];
	toH = params[3];
}

void WallAnimator::SetDestiny(float params[4], int Opacity)
{
	toX = params[0];
	toY = params[1];
	toW = params[2];
	toH = params[3];
	changeOpacity = true;
	initialOpacity = cs->sprite->getOpacity();
	finalOpacity = Opacity;
}

void WallAnimator::Animate(float percentage)
{
	float diffX = toX - fromX;
	float diffY = toY - fromY;
	float diffW = toW - fromW;
	float diffH = toH - fromH;

	float newPositionX = fromX + diffX * percentage;
	float newPositionY = fromY + diffY * percentage;
	float newPositionW = fromW + diffW * percentage;
	float newPositionH = fromH + diffH * percentage;

	cs->SetPosition(newPositionX, newPositionY);
	cs->SetSize(newPositionW, newPositionH);

	if (changeOpacity)
	{
		int diffOp = finalOpacity - initialOpacity;
		int newOp = initialOpacity + diffOp * percentage;
		cs->SetOpacity(newOp);
	}
}