#include "GameScene.h"
#include "MyFunctions.h"
#include "Vector2.h"
#include "Laberynth.h"
#include "CentSprite.h"
#include <vector>

USING_NS_CC;
using namespace std;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	/*auto background = Sprite::create("images/GameScreen/Background.png");
	MyFunctions::SetSprite(background, 0, 0, 100, 100);
	addChild(background, 0);*/

	auto ceiling = Sprite::create("images/GameScreen/CeilingTexture.jpg");
	MyFunctions::SetSprite(ceiling, 0, 45, 100, 55);
	addChild(ceiling, 0);

	auto floor = Sprite::create("images/GameScreen/GroundTexture.jpg");
	MyFunctions::SetSprite(floor, 0, 0, 100, 45);
	addChild(floor, 0);

	laberynth.Load(1, 1);

	Vector2* entrance = laberynth.GetEntrance();
	player.Position.x = entrance->x;
	player.Position.y = entrance->y;
	Vector2* size = laberynth.Size();
	if (player.Position.x == 0)
	{
		player.Direction = Vector2(1,0);
		player.Left = Vector2(0, 1);
	}
	else if (player.Position.x == size->x - 1)
	{
		player.Direction = Vector2(-1, 0);
		player.Left = Vector2(0, -1);
	}
	else if (player.Position.y == 0)
	{
		player.Direction = Vector2(0, 1);
		player.Left = Vector2(-1, 0);
	}
	else if (player.Position.y == size->y - 1)
	{
		player.Direction = Vector2(0, -1);
		player.Left = Vector2(1, 0);
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	debugg = Label::createWithTTF("(" + std::to_string(player.Position.x) + ", " + std::to_string(player.Position.y) + ")(" + std::to_string(player.Direction.x) + ", " + std::to_string(player.Direction.y) + "), (" + std::to_string(player.Left.x) + ", " + std::to_string(player.Left.y) + ")", "fonts/Marker Felt.ttf", 32);
	debugg->setPosition(Point(visibleSize.width / 2, visibleSize.height*0.6));
	debugg->setColor(ccc3(255, 0, 0));
	this->addChild(debugg, 2);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	updateView();

	return true;
}

//Hay que meter una funcion que cada enemy.duration haga enemy.whereIgo() y checkEnemyDirections, algo parecido a onKeyPressed , que haga mover al enemigo;

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W :
		if (player.canForward)
		{
			player.stepForward();
			updateView();
			checkPlayerDirections();
		}
		break;
	case EventKeyboard::KeyCode::KEY_S:
		if (player.canBackward)
		{
			player.stepBackward();
			updateView();
			checkPlayerDirections();
		}
		break;
	case EventKeyboard::KeyCode::KEY_A:
		player.turnLeft();
		updateView();
		checkPlayerDirections();
		break;
	case EventKeyboard::KeyCode::KEY_D:
		player.turnRight();
		updateView();
		checkPlayerDirections();
		break;
	}
}

void GameScene::checkPlayerDirections()
{
	int x = player.Position.x + player.Direction.x;
	int y = player.Position.y + player.Direction.y;
	if (laberynth.isIn(x, y) && !laberynth.isWall(x, y))
		player.canForward = true;
	else
		player.canForward = false;

	x = player.Position.x - player.Direction.x;
	y = player.Position.y - player.Direction.y;
	if (laberynth.isIn(x, y) && !laberynth.isWall(x, y))
		player.canBackward = true;
	else
		player.canBackward = false;
}

void GameScene::checkEnemyDirections(Enemy enemy){
	int x = enemy.Position.x + enemy.Direction.x;
	int y = enemy.Position.y + enemy.Direction.y;
	if (laberynth.isIn(x, y) && !laberynth.isWall(x, y))
		enemy.canForward = true;
	else
		enemy.canForward = false;

	x = enemy.Position.x - enemy.Direction.x;
	y = enemy.Position.y - enemy.Direction.y;
	if (laberynth.isIn(x, y) && !laberynth.isWall(x, y))
		enemy.canBackward = true;
	else
		enemy.canBackward = false;

	x = enemy.Position.x + enemy.Left.x;
	y = enemy.Position.y + enemy.Left.y;
	if (laberynth.isIn(x, y) && !laberynth.isWall(x, y))
		enemy.canLeft = true;
	else
		enemy.canLeft = false;

	x = enemy.Position.x - enemy.Left.x;
	y = enemy.Position.y - enemy.Left.y;
	if (laberynth.isIn(x, y) && !laberynth.isWall(x, y))
		enemy.canRight = true;
	else
		enemy.canRight = false;

}

void GameScene::findView()
{
	walls.clear();

	int x, y;
	bool avoidLeft = false, avoidRight = false;

	debugg->setString("(" + std::to_string(player.Position.x) + ", " + std::to_string(player.Position.y) + ")(" + std::to_string(player.Direction.x) + ", " + std::to_string(player.Direction.y) + "), (" + std::to_string(player.Left.x) + ", " + std::to_string(player.Left.y) + ")");

	//// NIVEL 1
	x = player.Position.x + player.Direction.x;
	y = player.Position.y + player.Direction.y;

	if (laberynth.isWall(x, y))
	{
		walls.push_back(new CentSprite("images/GameScreen/wallTexture.jpg", 0, 0, 100, 100));
		return;
	}
	else
	{
		if (laberynth.isWall(x + player.Left.x, y + player.Left.y))
		{
			avoidLeft = true;
			walls.push_back(new CentSprite("images/GameScreen/wallTexture2D.png", 27.7, 0, -20, 98));
		}
		if (laberynth.isWall(x - player.Left.x, y - player.Left.y))
		{
			avoidRight = true;
			walls.push_back(new CentSprite("images/GameScreen/wallTexture2D.png", 84.8, 0, 20, 98));
		}
	}

	//// NIVEL 2
	
	x += player.Direction.x;
	y += player.Direction.y;

	if (!laberynth.isIn(x, y)) return;

	if (!avoidLeft && laberynth.isWall(x + player.Left.x, y + player.Left.y))
	{
		avoidLeft = true;
		walls.push_back(new CentSprite("images/GameScreen/wallTexture.jpg", 5, 21.4, 19.7, 52));
	}
	if (!avoidRight && laberynth.isWall(x - player.Left.x, y - player.Left.y))
	{
		avoidRight = true;
		walls.push_back(new CentSprite("images/GameScreen/wallTexture.jpg", 84.8, 21.7, 20, 51));
	}

	avoidLeft = avoidRight = false;

	if (laberynth.isWall(x, y))
	{
		walls.push_back(new CentSprite("images/GameScreen/wallTexture.jpg", 20, 21.7, 63, 51.3));
	}
	else
	{
		if (laberynth.isWall(x + player.Left.x, y + player.Left.y))
		{
			avoidLeft = true;
			walls.push_back(new CentSprite("images/GameScreen/wallTexture2D.png", 36.5, 21.4, -10, 52));
		}
		if (laberynth.isWall(x - player.Left.x, y - player.Left.y))
		{
			avoidRight = true;
			walls.push_back(new CentSprite("images/GameScreen/wallTexture2D.png", 75.5, 21.7, 10, 51));
		}
	}

	//// NIVEL 3

	x += player.Direction.x;
	y += player.Direction.y;

	if (!laberynth.isIn(x, y)) return;

	if (!avoidLeft && laberynth.isWall(x + player.Left.x, y + player.Left.y))
	{
		avoidLeft = true;
		walls.push_back(new CentSprite("images/GameScreen/wallTexture.jpg", 3, 33, 30.9, 26.8));
	}
	if (!avoidRight && laberynth.isWall(x - player.Left.x, y - player.Left.y))
	{
		avoidRight = true;
		walls.push_back(new CentSprite("images/GameScreen/wallTexture.jpg", 74.3, 33, 31.2, 26.5));
	}

	avoidLeft = avoidRight = false;

	if (laberynth.isWall(x, y))
	{
		walls.push_back(new CentSprite("images/GameScreen/wallTexture.jpg", 30.8, 33, 43, 26.9));
	}
	else
	{
		if (laberynth.isWall(x + player.Left.x, y + player.Left.y))
		{
			avoidLeft = true;
			walls.push_back(new CentSprite("images/GameScreen/wallTexture2D.png", 41.1, 32.9, -5, 27));
		}
		if (laberynth.isWall(x - player.Left.x, y - player.Left.y))
		{
			avoidRight = true;
			walls.push_back(new CentSprite("images/GameScreen/wallTexture2D.png", 71, 33, 5, 26.5));
		}
	}

	//// NIVEL 4

	x += player.Direction.x;
	y += player.Direction.y;

	if (!laberynth.isIn(x, y)) return;

	if (!avoidLeft && laberynth.isWall(x + player.Left.x, y + player.Left.y))
	{
		avoidLeft = true;
		walls.push_back(new CentSprite("images/GameScreen/wallTexture.jpg", 3, 38.5, 35.3, 14.4));
	}
	if (!avoidRight && laberynth.isWall(x - player.Left.x, y - player.Left.y))
	{
		avoidRight = true;
		walls.push_back(new CentSprite("images/GameScreen/wallTexture.jpg", 69.2, 38.5, 36, 14.4));
	}

	avoidLeft = avoidRight = false;

	if (laberynth.isWall(x, y))
	{
		walls.push_back(new CentSprite("images/GameScreen/wallTexture.jpg", 36, 38.5, 34, 14.4));
	}
	else
	{
		if (laberynth.isWall(x + player.Left.x, y + player.Left.y))
		{
			avoidLeft = true;
			walls.push_back(new CentSprite("images/GameScreen/wallTexture2D.png", 43.2, 38.5, -2.5, 14.7));
		}
		if (laberynth.isWall(x - player.Left.x, y - player.Left.y))
		{
			avoidRight = true;
			walls.push_back(new CentSprite("images/GameScreen/wallTexture2D.png", 68.8, 38.5, 2.5, 14.7));
		}
	}
}

void GameScene::updateView()
{
	for (int i = 0; i < walls.size(); ++i)
	{
		removeChild(walls[i]->sprite);
		delete(walls[i]);
	}
	findView();
	for (int i = walls.size() - 1; i >= 0; --i)
		addChild(walls[i]->sprite);
}
