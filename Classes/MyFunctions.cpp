#include "MyFunctions.h"

USING_NS_CC;

void MyFunctions::SetSprite(cocos2d::Sprite* sprite, float x, float y, float width, float height)
{
	if (sprite != NULL)
	{
		//sprite->setAnchorPoint(Vec2(-0.063, 0));
		sprite->setAnchorPoint(Vec2(0, 0));

		auto director = Director::getInstance();
		Size screenSize = director->getVisibleSize();

		float positionX = screenSize.width * x / 100;
		float positionY = screenSize.height * y / 100;
		float sizeX = screenSize.width * width / 100;
		float sizeY = screenSize.height * height / 100;

		float scaleX = sizeX / sprite->getContentSize().width;
		float scaleY = sizeY / sprite->getContentSize().height;
		sprite->setScaleX(scaleX);
		sprite->setScaleY(scaleY);

		sprite->setPosition(positionX + sizeX*0.063, positionY);
		//sprite->setPosition(Point(positionX + sizeX / 1.78, screenSize.height - positionY - sizeY / 2));
	}
}

bool MyFunctions::IsIn(int x, int y, CentSprite* cs)
{
	if (x < cs->GetPosition().x) return false;
	if (x > cs->GetPosition().x + cs->GetSize().x) return false;
	if (y < cs->GetPosition().y) return false;
	if (y > cs->GetPosition().y + cs->GetSize().y) return false;

	return true;
}