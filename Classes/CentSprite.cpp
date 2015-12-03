#include "cocos2d.h"
#include "CentSprite.h"
#include "MyFunctions.h"
#include "Vector2F.h"

CentSprite::CentSprite(const char* spriteFile, float _x, float _y, float _width, float _height)
{
	sprite = Sprite::create(spriteFile);
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	MyFunctions::SetSprite(sprite, x, y, width, height);
	SetPosition(x, y);
	SetSize(width, height);
	Tag = "";
	orderZ = 2;
	sprite->setZOrder(orderZ);
}

CentSprite::CentSprite(char* spriteFile, float _x, float _y, float _width, float _height)
{
	sprite = Sprite::create(spriteFile);
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	MyFunctions::SetSprite(sprite, x, y, width, height);
	Tag = "";
	orderZ = 2;
	sprite->setZOrder(orderZ);
}

CentSprite::CentSprite(Sprite* _sprite, float _x, float _y, float _width, float _height)
{
	sprite = _sprite;
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	MyFunctions::SetSprite(sprite, x, y, width, height);
	Tag = "";
	orderZ = 2;
	sprite->setZOrder(orderZ);
}

CentSprite::CentSprite(const char* spriteFile, float _x, float _y, float _width, float _height, int order)
{
	sprite = Sprite::create(spriteFile);
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	MyFunctions::SetSprite(sprite, x, y, width, height);
	Tag = "";
	orderZ = order;
	sprite->setZOrder(orderZ);
}

CentSprite::CentSprite(char* spriteFile, float _x, float _y, float _width, float _height, int order)
{
	sprite = Sprite::create(spriteFile);
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	MyFunctions::SetSprite(sprite, x, y, width, height);
	Tag = "";
	orderZ = order;
	sprite->setZOrder(orderZ);
}

CentSprite::CentSprite(Sprite* _sprite, float _x, float _y, float _width, float _height, int order)
{
	sprite = _sprite;
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	MyFunctions::SetSprite(sprite, x, y, width, height);
	Tag = "";
	orderZ = order;
	sprite->setZOrder(orderZ);
}

///////// FIN CONSTRUCTORES

void CentSprite::SetPosition(float _x, float _y)
{
	x = _x;
	y = _y;
	auto director = Director::getInstance();
	Size screenSize = director->getVisibleSize();

	float positionX = screenSize.width * x / 100;
	float positionY = screenSize.height * y / 100;

	float sizeX = screenSize.width * GetSize().x / 100;
	float sizeY = screenSize.height * GetSize().y / 100;

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

Vector2F CentSprite::GetPosition() { return Vector2F(x, y); }

Vector2F CentSprite::GetSize() { return Vector2F(width, height); }

void CentSprite::SetOpacity(GLubyte opacity) { sprite->setOpacity(opacity); }

int CentSprite::GetOrderZ() { return orderZ; }
void CentSprite::SetOrderZ(int order)
{
	orderZ = order;
	sprite->setZOrder(orderZ);
}