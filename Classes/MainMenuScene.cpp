#include "MainMenuScene.h"
#include "GameMenu.h"
#include "MyFunctions.h"
#include "Assets.h"
#include <string>

USING_NS_CC;
using namespace std;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
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
		CC_CALLBACK_1(MainMenuScene::Play, this));
	auto menu = Menu::create(playItem, NULL);
	menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);
	menu->setPosition(Point(visibleSize.width/1.8, visibleSize.height/4));
	addChild(menu, 1);

	/*
	debugg = Label::createWithTTF(std::to_string(poscent.x) + ":" + std::to_string(pos.x) + ", " + std::to_string(poscent.y) + ":" + std::to_string(pos.y), "fonts/Marker Felt.ttf", 32);
	debugg->setPosition(Point(300, 100));
	debugg->setColor(ccc3(255, 0, 0));
	this->addChild(debugg, 2);*/

    return true;
}


void MainMenuScene::Play(Ref *pSender)
{
	auto scene = GameMenu::createScene();
	Director::getInstance()->replaceScene(scene);
}

