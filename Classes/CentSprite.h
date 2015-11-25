#ifndef __CENT_SPRITE_H__
#define __CENT_SPRITE_H__

#include "cocos2d.h"
#include "Vector2.h"

USING_NS_CC;

class CentSprite
{
private:
	float x, y, width, height;

public:
	Sprite* sprite;
	void SetPosition(float, float);
	void SetSize(float, float);
	Vector2 GetPosition();
	Vector2 GetSize();
	
	CentSprite();
	CentSprite(Sprite*, float, float, float, float);
	CentSprite(char*, float, float, float, float);

};

#endif 


