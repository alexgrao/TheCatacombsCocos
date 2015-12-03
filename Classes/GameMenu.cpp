#include "cocos2d.h"
#include "GameMenu.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include "MyFunctions.h"
#include "Assets.h"
#include "CentSprite.h"

USING_NS_CC;
using namespace std;

Scene* GameMenu::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameMenu::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameMenu::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	/*Catacomb = 1;
	Level = 1;*/

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto background = Sprite::create(Assets::MenuBackground);
	MyFunctions::SetSprite(background, 0, 0, 100, 100);
	addChild(background, 0);

	/////////////////////  MAPA EUROPA

	CentSprite* europeMap = new CentSprite(Assets::EUMap, 5, 45, 90, 50);
	addChild(europeMap->sprite);

	Madrid = new CentSprite(Assets::RedBall, 23.5, 62.5, 2, 2);
	addChild(Madrid->sprite);
	London = new CentSprite(Assets::RedBall, 33, 77, 2, 2);
	addChild(London->sprite);
	Rome = new CentSprite(Assets::RedBall, 46, 61, 2, 2);
	addChild(Rome->sprite);
	Berlin = new CentSprite(Assets::RedBall, 45, 75, 2, 2);
	addChild(Berlin->sprite);

	/////////////////////////////////////////

	// DEBUGG LABEL
	debugg = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 15);
	debugg->setPosition(Point(visibleSize.width * 0.6, visibleSize.height*0.6));
	debugg->setColor(ccc3(255, 0, 0));
	this->addChild(debugg, 20);

	// Creating menu
	auto playItem = MenuItemImage::create(Assets::PlayButton,
		Assets::PlayButtonClicked,
		CC_CALLBACK_1(GameMenu::Play, this));
	auto menu = Menu::create(playItem, NULL);
	menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);
	menu->setPosition(Point(visibleSize.width / 1.8, visibleSize.height / 4));
	addChild(menu, 1);

	// MOUSE EVENT FOR CITIES BUTTONS
	auto listenerMouse = EventListenerMouse::create();
	listenerMouse->onMouseMove = CC_CALLBACK_1(GameMenu::OnMouseMove, this);
	listenerMouse->onMouseDown = CC_CALLBACK_1(GameMenu::OnMouseDown, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerMouse, this);

	return true;
}


void GameMenu::Play(Ref *pSender)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->pushScene(scene);
}

void GameMenu::BackToMainMenu(Ref *pSender)
{
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void GameMenu::OnMouseMove(Event *event)
{
	EventMouse *e = (EventMouse*)event;

	int x = e->getCursorX();
	int y = e->getCursorY();

	if (overCity != 1 && MyFunctions::IsIn(x, y, Madrid))
	{
		if (selectedCity != 1)
			MarkCity(true, 1);
		else
			overCity = 1;
	}
	else if (overCity == 1 && !MyFunctions::IsIn(x, y, Madrid))
	{
		if (selectedCity != 1)
			MarkCity(false, 1);
		else
			overCity = 0;
	}
	// Lo mismo con Londres
	if (overCity != 2 && MyFunctions::IsIn(x, y, London))
	{
		if (selectedCity != 2)
			MarkCity(true, 2);
		else
			overCity = 2;
	}
	else if (overCity == 2 && !MyFunctions::IsIn(x, y, London))
	{
		if (selectedCity != 2)
			MarkCity(false, 2);
		else
			overCity = 0;
	}
	// Lo mismo con Roma
	if (overCity != 3 && MyFunctions::IsIn(x, y, Rome))
	{
		if (selectedCity != 3)
			MarkCity(true, 3);
		else
			overCity = 3;
	}
	else if (overCity == 3 && !MyFunctions::IsIn(x, y, Rome))
	{
		if (selectedCity != 3)
			MarkCity(false, 3);
		else
			overCity = 0;
	}
	// Lo mismo con Berlin
	if (overCity != 4 && MyFunctions::IsIn(x, y, Berlin))
	{
		if (selectedCity != 4)
			MarkCity(true, 4);
		else
			overCity == 4;
	}
	else if (overCity == 4 && !MyFunctions::IsIn(x, y, Berlin))
	{
		if (selectedCity != 4)
			MarkCity(false, 4);
		else
			overCity = 0;
	}

}

void GameMenu::OnMouseDown(Event *event)
{
	if (overCity == 0) return;
	if (overCity == selectedCity) return;

	int over = overCity;
	if (selectedCity != 0) MarkCity(false, selectedCity);
	overCity = over;

	selectedCity = overCity;
}

void GameMenu::MarkCity(bool Big, int index)
{
	float newSize = 5;
	float diff = newSize - 2;

	CentSprite* cs;
	if (index == 1)
		cs = Madrid;
	else if (index == 2)
		cs = London;
	else if (index == 3)
		cs = Rome;
	else if (index == 4)
		cs = Berlin;

	if (Big)
	{
		cs->SetSize(newSize, newSize);
		cs->SetPosition(cs->GetPosition().x - diff / 2, cs->GetPosition().y - diff / 2);
		overCity = index;
	}
	else
	{
		cs->SetPosition(cs->GetPosition().x + diff / 2, cs->GetPosition().y + diff / 2);
		cs->SetSize(2, 2);
		overCity = 0;
	}
}