#ifndef __CENT_SPRITE_H__
#define __CENT_SPRITE_H__

#include "cocos2d.h"
#include "Vector2F.h"

USING_NS_CC;

class CentSprite
{
private:
	float x, y, width, height;
	int orderZ;

public:
	Sprite* sprite;
	void SetPosition(float, float);
	void SetSize(float, float);
	Vector2F GetPosition();
	Vector2F GetSize();
	const char* Tag;
	void SetOpacity(GLubyte);
	int GetOrderZ();
	void SetOrderZ(int);
	
	//CentSprite();
	CentSprite(Sprite*, float, float, float, float);
	CentSprite(const char*, float, float, float, float);
	CentSprite(char*, float, float, float, float);
	CentSprite(Sprite*, float, float, float, float, int);
	CentSprite(const char*, float, float, float, float, int);
	CentSprite(char*, float, float, float, float, int);

};

#endif 


