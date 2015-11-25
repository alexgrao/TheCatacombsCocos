#include "cocos2d.h"
#include "CentSprite.h"
#include "MyFunctions.h"
#include "Vector2.h"

CentSprite::CentSprite(Sprite* _sprite, float _x, float _y, float _width, float _height)
{
	sprite = _sprite;
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	MyFunctions::SetSprite(sprite, x, y, width, height);
}

CentSprite::CentSprite(char* spriteFile, float _x, float _y, float _width, float _height)
{
	sprite = Sprite::create(spriteFile);
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	MyFunctions::SetSprite(sprite, x, y, width, height);
}

void CentSprite::SetPosition(float _x, float _y)
{
	x = _x;
	y = _y;
	auto director = Director::getInstance();
	Size screenSize = director->getVisibleSize();

	float positionX = screenSize.width * x / 100;
	float positionY = screenSize.height * y / 100;
	float sizeX = sprite->getContentSize().width;
	float sizeY = sprite->getContentSize().height;

	sprite->setPosition(Point(positionX + sizeX*0.063, positionY));
}

void CentSprite::SetSize(float _width, float _height)
{
	width = _width;
	height = _height;
	auto director = Director::getInstance();
	Size screenSize = director->getVisibleSize();

	float sizeX = screenSize.width * width / 100;
	float sizeY = screenSize.height * height / 100;
	float scaleX = sizeX / sprite->getContentSize().width;
	float scaleY = sizeY / sprite->getContentSize().height;

	sprite->setScaleX(scaleX);
	sprite->setScaleY(scaleY);
}

Vector2 CentSprite::GetPosition() { return Vector2(x, y); }

Vector2 CentSprite::GetSize() { return Vector2(x, y); }