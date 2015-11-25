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

	CentSprite* europeMap = new CentSprite(Assets::EUMap, 5, 45, 90, 50);
	addChild(europeMap->sprite);

	// Creating menu
	auto playItem = MenuItemImage::create(Assets::PlayButton,
		Assets::PlayButtonClicked,
		CC_CALLBACK_1(GameMenu::Play, this));
	auto menu = Menu::create(playItem, NULL);
	menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);
	menu->setPosition(Point(visibleSize.width / 1.8, visibleSize.height / 4));
	addChild(menu, 1);

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
