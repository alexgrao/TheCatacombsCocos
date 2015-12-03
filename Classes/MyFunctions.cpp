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

		sprite->setPosition(positionX + sizeX*0.063, positionY);

		float scaleX = sizeX / sprite->getContentSize().width;
		float scaleY = sizeY / sprite->getContentSize().height;
		sprite->setScaleX(scaleX);
		sprite->setScaleY(scaleY);

		//sprite->setPosition(Point(positionX + sizeX / 1.78, screenSize.height - positionY - sizeY / 2));
	}
}

bool MyFunctions::IsIn(int x, int y, CentSprite* cs)
{
	auto director = Director::getInstance();
	Size screenSize = director->getVisibleSize();
	float percentageX = (float)x * 100 / screenSize.width; // x = z%Screen.width  z = x*100 / Screen.width
	float percentageY = (float)y * 100 / screenSize.height;

	if (percentageX < cs->GetPosition().x) return false;
	if (percentageX > cs->GetPosition().x + cs->GetSize().x) return false;
<<<<<<< HEAD
	if (percentageY < cs->GetPosition().y + 2) return false;
	if (percentageY > cs->GetPosition().y + cs->GetSize().y + 2) return false;
=======
	if (percentageY < cs->GetPosition().y) return false;
	if (percentageY > cs->GetPosition().y+ cs->GetSize().y) return false;
>>>>>>> origin/master

	return true;
}