#include "cocos2d.h"
#include "GameMenu.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include "MyFunctions.h"
#include "Assets.h"
#include "CentSprite.h"
#include "SimpleAudioEngine.h"

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

	float newSize = 5;
	float diff = newSize - 2;

	// Si estamos sobre el boton de Madrid y antes no estabamos
	if (overCity != 1 && MyFunctions::IsIn(x, y, Madrid))
	{
		// Aumenta el tamaño y márcalo
		Vector2F before = Madrid->GetPosition();

		Madrid->SetSize(newSize, newSize);
		Madrid->SetPosition(Madrid->GetPosition().x - diff / 2, Madrid->GetPosition().y - diff / 2);
		overCity = 1;

		debugg->setString(std::to_string(before.x) + ", " + std::to_string(before.y) + " / " + std::to_string(Madrid->GetPosition().x) + ", " + std::to_string(Madrid->GetPosition().y));
	}
	// Si estabamos pero ahora ya no estamos sobre el boton
	else if (overCity == 1 && !MyFunctions::IsIn(x, y, Madrid))
	{
		// Devuelvelo a su tamaño original y desmárcalo
		Madrid->SetPosition(Madrid->GetPosition().x + diff / 2, Madrid->GetPosition().y + diff / 2);
		Madrid->SetSize(2, 2);
		overCity = 0;
	}
	// Lo mismo con Londres
	else if (overCity != 2 && MyFunctions::IsIn(x, y, London))
	{
		London->SetSize(newSize, newSize);
		London->SetPosition(London->GetPosition().x - newSize / 4, London->GetPosition().y - newSize / 4);
		overCity = 2;
	}
	else if (overCity == 2 && !MyFunctions::IsIn(x, y, London))
	{
		London->SetPosition(London->GetPosition().x + newSize / 2, London->GetPosition().y + newSize / 2);
		London->SetSize(2, 2);
		overCity = 0;
	}
	// Lo mismo con Roma
	else if (overCity != 3 && MyFunctions::IsIn(x, y, Rome))
	{
		Rome->SetSize(newSize, newSize);
		Rome->SetPosition(Rome->GetPosition().x - newSize / 4, Rome->GetPosition().y - newSize / 4);
		overCity = 3;
	}
	else if (overCity == 3 && !MyFunctions::IsIn(x, y, Rome))
	{
		Rome->SetPosition(Rome->GetPosition().x + newSize / 2, Rome->GetPosition().y + newSize / 2);
		Rome->SetSize(2, 2);
		overCity = 0;
	}
	// Lo mismo con Berlin
	else if (overCity != 4 && MyFunctions::IsIn(x, y, Berlin))
	{
		Berlin->SetSize(newSize, newSize);
		Berlin->SetPosition(Berlin->GetPosition().x - newSize / 4, Berlin->GetPosition().y - newSize / 4);
		overCity = 4;
	}
	else if (overCity == 4 && !MyFunctions::IsIn(x, y, Berlin))
	{
		Berlin->SetPosition(Berlin->GetPosition().x + newSize / 2, Berlin->GetPosition().y + newSize / 2);
		Berlin->SetSize(2, 2);
		overCity = 0;
	}
}

void GameMenu::OnMouseDown(Event *event)
{
	EventMouse *e = (EventMouse*)event;

	int x = e->getCursorX();
	int y = e->getCursorY();
}