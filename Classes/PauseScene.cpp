#include "PauseScene.h"
#include "MyFunctions.h"
#include "Assets.h"
#include <string>

USING_NS_CC;
using namespace std;

Scene* PauseScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = PauseScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool PauseScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto background = Sprite::create(Assets::MenuBackground);
	MyFunctions::SetSprite(background, 0, 0, 100, 100);
	addChild(background, 0);

	// menu title
	auto title = Sprite::create(Assets::MenuTitle);
	MyFunctions::SetSprite(title, 30, 70, 50, 15);
	addChild(title, 1);

	// Creating menu
	auto playItem = MenuItemImage::create(Assets::PlayButton,
		Assets::PlayButtonClicked,
		CC_CALLBACK_1(PauseScene::ResumeGame, this));
	auto menu = Menu::create(playItem, NULL);
	menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);
	menu->setPosition(Point(visibleSize.width / 1.8, visibleSize.height / 4));
	addChild(menu, 1);

	// KEY EVENT FOR GOING BACK TO GAME
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(PauseScene::onKeyPressed, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}


void PauseScene::ResumeGame(Ref *pSender)
{
	Director::getInstance()->getOpenGLView()->setCursorVisible(false);
	Director::getInstance()->popScene();
}

void PauseScene::GoToGameMenu(Ref *pSender)
{
	Director::getInstance()->popScene();
	Director::getInstance()->popScene();
}

void PauseScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		ResumeGame(this);
		break;
	}
}
