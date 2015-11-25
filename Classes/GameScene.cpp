#include "GameScene.h"
#include "MyFunctions.h"
#include "Vector2.h"
#include "Vector2F.h"
#include "Laberynth.h"
#include "CentSprite.h"
#include "Assets.h"
#include <vector>
#include "PauseScene.h"
#include "GameMenu.h"

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

	/*catacomb = GameMenu::Catacomb;
	level = GameMenu::Level;*/

	auto ceiling = Sprite::create(Assets::Ceiling);
	MyFunctions::SetSprite(ceiling, 0, 45, 100, 55);
	addChild(ceiling, 0);

	auto floor = Sprite::create(Assets::Floor);
	MyFunctions::SetSprite(floor, 0, 0, 100, 45);
	addChild(floor, 0);

	laberynth.Load(1, 1);

	loadPlayer();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	// KEY EVENT FOR MOVING
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	findEnemies();

	// DEBUGG LABEL
	debugg = Label::createWithTTF("Tiempo: 0", "fonts/Marker Felt.ttf", 32);
	debugg->setPosition(Point(visibleSize.width / 2, visibleSize.height*0.6));
	debugg->setColor(ccc3(255, 0, 0));
	this->addChild(debugg, 5);

	// Update walls view
	updateView();

	// start timer
	time = 0;
	this->scheduleUpdate();

	Director::getInstance()->getOpenGLView()->setCursorVisible(false);
	cross = Sprite::create(Assets::Cross);
	cross->setScale(0.1);
	addChild(cross, 10);
	recoil = Vector2F(0, 0);
	mousePosition = Vector2F(0, 0);
	delta = Vector2F(0, 0);

	// MOUSE EVENT FOR CROSS
	auto listenerMouse = EventListenerMouse::create();
	listenerMouse->onMouseMove = CC_CALLBACK_1(GameScene::OnMouseMove, this);
	listenerMouse->onMouseDown = CC_CALLBACK_1(GameScene::OnMouseDown, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerMouse, this);

	return true;
}

void GameScene::loadPlayer()
{
	Vector2* entrance = laberynth.GetEntrance();
	player.Position.x = entrance->x;
	player.Position.y = entrance->y;
	Vector2* size = laberynth.Size();
	if (player.Position.x == 0)
	{
		player.Direction = Vector2(1, 0);
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
}

void GameScene::findEnemies()
{
	for (int i = 0; i < laberynth.Size()->x; ++i)
	{
		for (int j = 0; j < laberynth.Size()->y; ++j)
		{
			int n = laberynth.Get(i, j);
			if (n > 10)
			{
				Enemy* e = new Enemy(n - 10);
				enemies.push_back(e);
				e->SetPosition(i, j);
				e->SearchInitialDirection(&laberynth);
				laberynth.Set(i, j, enemies.size()-1 + 10);

				Sprite* enemySprite = Sprite::create(e->GetSprite());
				enemiesSprites.push_back(new CentSprite(enemySprite, 0, 0, 0, 0));
				addChild(enemySprite);
			}
		}
	}
}

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
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		PauseGame(this);
		break;
	// ESTOS SON PARA TESTEAR, QUITAR LUEGO
	case EventKeyboard::KeyCode::KEY_E:
		++enemies[0]->channel;
		if (enemies[0]->channel == 4) enemies[0]->channel = 0;
		findEnemyView(0);
		break;
	case EventKeyboard::KeyCode::KEY_Q:
		--enemies[0]->channel;
		if (enemies[0]->channel == -1) enemies[0]->channel = 3;
		findEnemyView(0);
		break;
	}
}

void GameScene::checkPlayerDirections()
{
	int x = player.Position.x + player.Direction.x;
	int y = player.Position.y + player.Direction.y;
	if (laberynth.isIn(x, y) && !laberynth.isWall(x, y) && !laberynth.isExitEntrance(x,y))
		player.canForward = true;
	else
		player.canForward = false;

	x = player.Position.x - player.Direction.x;
	y = player.Position.y - player.Direction.y;
	if (laberynth.isIn(x, y) && !laberynth.isWall(x, y) && !laberynth.isExitEntrance(x, y))
		player.canBackward = true;
	else
		player.canBackward = false;
}

void GameScene::findView()
{
	walls.clear();

	int x, y;
	bool avoidLeft = false, avoidRight = false;

	//// NIVEL 1
	x = player.Position.x + player.Direction.x;
	y = player.Position.y + player.Direction.y;

	if (laberynth.isWall(x, y))
	{
		walls.push_back(new CentSprite(Assets::Wall, 0, 0, 100, 100));
		return;
	}
	/*else if (laberynth.isExitEntrance(x, y))
	{
		int n = laberynth.Get(x, y);
		if (n == 3)
			walls.push_back(new CentSprite(Assets::Upstairs, 0, 0, 100, 100));
		else
			walls.push_back(new CentSprite(Assets::Downstairs, 0, 0, 100, 100));
		return;
	}*/
	else
	{
		// IZQUIERDA
		if (laberynth.isWall(x + player.Left.x, y + player.Left.y))
		{
			avoidLeft = true;
			walls.push_back(new CentSprite(Assets::ShadowOverWall, 27.7, 0, -20, 98, 6));
			walls[walls.size() - 1]->SetOpacity(90);
			walls.push_back(new CentSprite(Assets::Wall3D, 27.7, 0, -20, 98, 6));
		}
		// DERECHA
		if (laberynth.isWall(x - player.Left.x, y - player.Left.y))
		{
			avoidRight = true;
			walls.push_back(new CentSprite(Assets::ShadowOverWall, 84.8, 0, 20, 98, 6));
			walls[walls.size() - 1]->SetOpacity(90);
			walls.push_back(new CentSprite(Assets::Wall3D, 84.8, 0, 20, 98, 6));
		}
	}

	/////////// SHADOW 0

	CentSprite* s0 = new CentSprite(Assets::Shadow, 0, 10, 100, 80, 6);
	walls.push_back(s0);
	s0->SetOpacity(90);

	//// NIVEL 2
	
	x += player.Direction.x;
	y += player.Direction.y;

	if (!laberynth.isIn(x, y)) return;

	if (!avoidLeft)
	{
		if (laberynth.isWall(x + player.Left.x, y + player.Left.y))
		{
			walls.push_back(new CentSprite(Assets::Wall, 5, 21.4, 19.7, 52, 6));
		}
		/*else if (laberynth.isExitEntrance(x + player.Left.x, y + player.Left.y))
		{
			int n = laberynth.Get(x, y);
			if (n == 3)
				walls.push_back(new CentSprite(Assets::Upstairs, 5, 21.4, 19.7, 52));
			else
				walls.push_back(new CentSprite(Assets::Downstairs, 5, 21.4, 19.7, 52));
		}*/
	}

	if (!avoidRight)
	{
		if (laberynth.isWall(x - player.Left.x, y - player.Left.y))
		{
			walls.push_back(new CentSprite(Assets::Wall, 84.8, 21.7, 20, 51, 6));
		}
		/*else if (laberynth.isExitEntrance(x - player.Left.x, y - player.Left.y))
		{
			int n = laberynth.Get(x, y);
			if (n == 3)
				walls.push_back(new CentSprite(Assets::Upstairs, 84.8, 21.7, 20, 51));
			else
				walls.push_back(new CentSprite(Assets::Downstairs, 84.8, 21.7, 20, 51));
		}*/
	}

	avoidLeft = avoidRight = false;

	if (laberynth.isWall(x, y))
	{
		walls.push_back(new CentSprite(Assets::Wall, 20, 21.7, 63, 51.3, 6));
	}
	/*else if (laberynth.isExitEntrance(x,y))
	{
		int n = laberynth.Get(x, y);
		if (n == 3)
			walls.push_back(new CentSprite(Assets::Upstairs, 20, 21.7, 63, 51.3));
		else
			walls.push_back(new CentSprite(Assets::Downstairs, 20, 21.7, 63, 51.3));
	}*/
	else
	{

		// IZQUIERDA
		if (laberynth.isWall(x + player.Left.x, y + player.Left.y))
		{
			avoidLeft = true;
			walls.push_back(new CentSprite(Assets::ShadowOverWall, 36.5, 21.4, -10, 52, 5));
			walls[walls.size() - 1]->SetOpacity(150);
			walls.push_back(new CentSprite(Assets::Wall3D, 36.5, 21.4, -10, 52, 5));
		}
		//DERECHA
		if (laberynth.isWall(x - player.Left.x, y - player.Left.y))
		{
			avoidRight = true;
			walls.push_back(new CentSprite(Assets::ShadowOverWall, 75.5, 21.7, 10, 51, 5));
			walls[walls.size() - 1]->SetOpacity(150);
			walls.push_back(new CentSprite(Assets::Wall3D, 75.5, 21.7, 10, 51, 5));
		}
	}

	/////////// SHADOW 1

	CentSprite* s1 = new CentSprite(Assets::Shadow, 0, 20, 100, 60, 5);
	walls.push_back(s1);
	s1->SetOpacity(150);

	//// NIVEL 3

	x += player.Direction.x;
	y += player.Direction.y;

	if (!laberynth.isIn(x, y)) return;

	//IZQUIERDA
	if (!avoidLeft)
	{
		if (laberynth.isWall(x + player.Left.x, y + player.Left.y))
		{
			walls.push_back(new CentSprite(Assets::Wall, 3, 33, 30.9, 26.8, 5));
		}
		/*else if (laberynth.isExitEntrance(x + player.Left.x, y + player.Left.y))
		{
			int n = laberynth.Get(x, y);
			if (n == 3)
				walls.push_back(new CentSprite(Assets::Upstairs, 3, 33, 30.9, 26.8));
			else
				walls.push_back(new CentSprite(Assets::Downstairs, 3, 33, 30.9, 26.8));
		}*/
	}

	//DERECHA
	if (!avoidRight) 
	{
		if (laberynth.isWall(x - player.Left.x, y - player.Left.y))
		{
			walls.push_back(new CentSprite(Assets::Wall, 74.3, 33, 31.2, 26.5, 5));
		}
		/*else if (laberynth.isExitEntrance(x - player.Left.x, y - player.Left.y))
		{
			int n = laberynth.Get(x, y);
			if (n == 3)
				walls.push_back(new CentSprite(Assets::Upstairs, 74.3, 33, 31.2, 26.5));
			else
				walls.push_back(new CentSprite(Assets::Downstairs, 74.3, 33, 31.2, 26.5));
		}*/
	}

	avoidLeft = avoidRight = false;

	if (laberynth.isWall(x, y))
	{
		walls.push_back(new CentSprite(Assets::Wall, 30.8, 33, 43, 26.9, 5));
	}
	/*else if (laberynth.isExitEntrance(x, y))
	{
		int n = laberynth.Get(x, y);
		if (n == 3)
			walls.push_back(new CentSprite(Assets::Upstairs, 30.8, 33, 43, 26.9));
		else
			walls.push_back(new CentSprite(Assets::Downstairs, 30.8, 33, 43, 26.9));
	}*/
	else
	{
		// IZQUIERDA
		if (laberynth.isWall(x + player.Left.x, y + player.Left.y))
		{
			avoidLeft = true;
			// wall shadow
			walls.push_back(new CentSprite(Assets::ShadowOverWall, 41.1, 32.9, -5, 27, 4));
			walls[walls.size() - 1]->SetOpacity(150);
			walls.push_back(new CentSprite(Assets::Wall3D, 41.1, 32.9, -5, 27, 4));
		}
		// DERECHA
		if (laberynth.isWall(x - player.Left.x, y - player.Left.y))
		{
			avoidRight = true;
			// wall shadow
			walls.push_back(new CentSprite(Assets::ShadowOverWall, 71, 33, 5, 26.5, 4));
			walls[walls.size() - 1]->SetOpacity(150);
			walls.push_back(new CentSprite(Assets::Wall3D, 71, 33, 5, 26.5, 4));
		}
	}

	/////////// SHADOW 2

	CentSprite* s2 = new CentSprite(Assets::Shadow, 0, 32.5, 100, 30, 4);
	walls.push_back(s2);
	s2->SetOpacity(150);

	//// NIVEL 4

	x += player.Direction.x;
	y += player.Direction.y;

	if (!laberynth.isIn(x, y)) return;

	if (!avoidLeft)
	{
		if (laberynth.isWall(x + player.Left.x, y + player.Left.y))
		{
			walls.push_back(new CentSprite(Assets::Wall, 3, 38.5, 35.3, 14.4, 4));
		}
		/*else if (laberynth.isExitEntrance(x + player.Left.x, y + player.Left.y))
		{
			int n = laberynth.Get(x, y);
			if (n == 3)
				walls.push_back(new CentSprite(Assets::Upstairs, 3, 38.5, 35.3, 14.4));
			else
				walls.push_back(new CentSprite(Assets::Downstairs, 3, 38.5, 35.3, 14.4));
		}*/
	}

	if (!avoidRight)
	{
		if (laberynth.isWall(x - player.Left.x, y - player.Left.y))
		{
			walls.push_back(new CentSprite(Assets::Wall, 69.2, 38.5, 36, 14.4, 4));
		}
		/*else
		{
			int n = laberynth.Get(x, y);
			if (n == 3)
				walls.push_back(new CentSprite(Assets::Upstairs, 69.2, 38.5, 36, 14.4));
			else
				walls.push_back(new CentSprite(Assets::Downstairs, 69.2, 38.5, 36, 14.4));
		}*/
	}

	avoidLeft = avoidRight = false;

	if (laberynth.isWall(x, y))
	{
		walls.push_back(new CentSprite(Assets::Wall, 36, 38.5, 34, 14.4, 4));
	}
	/*else if (laberynth.isExitEntrance(x, y))
	{
		int n = laberynth.Get(x, y);
		if (n == 3)
			walls.push_back(new CentSprite(Assets::Upstairs, 36, 38.5, 34, 14.4));
		else
			walls.push_back(new CentSprite(Assets::Downstairs, 36, 38.5, 34, 14.4));
	}*/
	else
	{

		//IZQUIERDA
		if (laberynth.isWall(x + player.Left.x, y + player.Left.y))
		{
			avoidLeft = true;
			walls.push_back(new CentSprite(Assets::Wall3D, 43.2, 38.5, -2.5, 14.7, 3));
		}
		// DERECHA
		if (laberynth.isWall(x - player.Left.x, y - player.Left.y))
		{
			avoidRight = true;
			walls.push_back(new CentSprite(Assets::Wall3D, 68.8, 38.5, 2.5, 14.7, 3));
		}
	}

	/////////// SHADOW 3

	CentSprite* s3 = new CentSprite(Assets::Shadow, 0, 38.5, 100, 15, 3);
	walls.push_back(s3);
	s3->SetOpacity(255);
}

void GameScene::findEnemyView(int i)
{
	Enemy* e = enemies[i];
	int distanceLateral = 0;
	int distanceFrontal;
	int sense;

	if (player.Left.y == 0)
	{
		distanceLateral = player.Position.x - e->Position.x;
		distanceLateral *= player.Direction.y;
		distanceFrontal = player.Position.y - e->Position.y;
		sense = player.Direction.y;
	}
	else
	{
		distanceLateral = player.Position.y - e->Position.y;
		distanceLateral *= player.Direction.x;
		distanceFrontal = player.Position.x - e->Position.x;
		sense = player.Direction.x;
	}

	// Si no está lateralmente visible
	if (distanceLateral < -1 || distanceLateral > 1)
	{
		enemiesSprites[i]->SetPosition(-100, -100);
		return;
	}

	// si el jugador mira en dirección contraria
	if (distanceFrontal > 0 && sense > 0)
	{
		enemiesSprites[i]->SetPosition(-100, -100);
		return;
	}
	if (distanceFrontal < 0 && sense < 0)
	{
		enemiesSprites[i]->SetPosition(-100, -100);
		return;
	}

	if (distanceFrontal < 0) distanceFrontal *= -1;

	// si está demasiado lejos
	if (distanceFrontal > 4)
	{
		enemiesSprites[i]->SetPosition(-100, -100);
		return;
	}
	if (distanceFrontal < 0)
	{
		enemiesSprites[i]->SetPosition(-100, -100);
		return;
	}

	enemiesSprites[i]->SetOrderZ(7 - distanceFrontal);

	switch (distanceFrontal)
	{
	case 0:
		if (distanceLateral == 0)
		{
			enemiesSprites[i]->SetPosition(20, 20);
			enemiesSprites[i]->SetSize(60, 60);
		}
		break;
	case 1:
		if (distanceLateral == -1)
			enemiesSprites[i]->SetPosition(-55 + 20 * e->channel, -1);
		else if (distanceLateral == 0)
			enemiesSprites[i]->SetPosition(7 + 20 * e->channel, -1);
		else if (distanceLateral == 1)
			enemiesSprites[i]->SetPosition(75 + 20 * e->channel, -1);
		enemiesSprites[i]->SetSize(27, 33.75);
		break;
	case 2:
		if (distanceLateral == -1)
			enemiesSprites[i]->SetPosition(-25 + 13 * e->channel, 21.7);
		else if (distanceLateral == 0)
			enemiesSprites[i]->SetPosition(20 + 13 * e->channel, 21.7);
		else if (distanceLateral == 1)
			enemiesSprites[i]->SetPosition(65 + 13 * e->channel, 21.7);
		enemiesSprites[i]->SetSize(18, 22.5);
		break;
	case 3:
		if (distanceLateral == -1)
			enemiesSprites[i]->SetPosition(-5 + 9.1 * e->channel, 33);
		else if (distanceLateral == 0)
			enemiesSprites[i]->SetPosition(30 + 9.1 * e->channel, 33);
		else if (distanceLateral == 1)
			enemiesSprites[i]->SetPosition(65 + 9.1 * e->channel, 33);
		enemiesSprites[i]->SetSize(12, 15);
		break;
	case 4:
		if (distanceLateral == -1)
			enemiesSprites[i]->SetPosition(5 + 7.5 * e->channel, 38.5);
		else if (distanceLateral == 0)
			enemiesSprites[i]->SetPosition(35 + 7.5 * e->channel, 38.5);
		else if (distanceLateral == 1)
			enemiesSprites[i]->SetPosition(65 + 7.5 * e->channel, 38.5);
		enemiesSprites[i]->SetSize(8, 10);
		break;
	default:
		enemiesSprites[i]->SetPosition(-100,-100);
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
		addChild(walls[i]->sprite, walls[i]->GetOrderZ());

	for (int i = 0; i< enemies.size(); ++i)
		if (enemies[i]->GetLifes() > 0) findEnemyView(i);

}

// FUNCTION UPDATE()
void GameScene::update(float delta)
{
	time += delta;

	for (int i = 0; i < enemies.size(); ++i)
	{
		Enemy* e = enemies[i];
		if (e->GetLifes() > 0 && e->CheckTimer(delta))
		{

			Vector2 prev = e->Position.Copy();
			e->whereIgo(&laberynth);
			e->stepForward();
			laberynth.MoveEnemy(prev.x, prev.y, e->Position.x, e->Position.y);
			findEnemyView(i);
		}
	}

	// cross movement

	cross->setPosition(Vec2(mousePosition.x + recoil.x, mousePosition.y + recoil.y));
	recoil.x *= 0.99;
	recoil.y *= 0.95;
	if (recoil.x < 1) recoil.x = 0;
	if (recoil.y < 1) recoil.y = 0;
}

void GameScene::OnMouseMove(Event *event)
{
	EventMouse *e = (EventMouse*)event;

	int x = e->getCursorX();
	int y = e->getCursorY();
	// al inicio del juego
	if (time < 0.1)
	{
		mousePosition = Vector2F(x, y);
	}

	delta.x = x - mousePosition.x;
	delta.y = y - mousePosition.y;

	float delay = 5;
	mousePosition.x += delta.x/delay;
	mousePosition.y += delta.y/delay;
}

void GameScene::OnMouseDown(Event *event)
{
	mousePosition.x += recoil.x;
	mousePosition.y += recoil.y;
	int rangoX = 10, rangoY = 25;
	int hor = cocos2d::RandomHelper::random_int(-rangoX, rangoX);
	int ver = cocos2d::RandomHelper::random_int(rangoY/2, rangoY);
	recoil = Vector2F(hor, ver);

	checkPressedOnEnemies(mousePosition.x, mousePosition.y);
}

void GameScene::checkPressedOnEnemies(int x, int y)
{
	auto director = Director::getInstance();
	Size screenSize = director->getVisibleSize();
	float percentageX = x * 100 / screenSize.width; // x = z%Screen.width  z = x*100 / Screen.width
	float percentageY = y * 100 / screenSize.height;

	for (int i = 0; i < enemiesSprites.size(); ++i)
	{
		CentSprite* cs = enemiesSprites[i];
		if (cs->GetPosition().x < 0) continue;

		if (MyFunctions::IsIn(percentageX, percentageY, cs))
		{
			Enemy* e = enemies[i];
			if (e->Damage())
			{
				debugg->setString("Muerto!");
				laberynth.Set(e->Position.x, e->Position.y, 0);
				cs->SetPosition(-100, -100);
				removeChild(cs->sprite);
			}
			else
				debugg->setString("Shot! Quedan " + std::to_string(enemies[i]->GetLifes()));
		}
	}
}

void GameScene::DeleteEverything()
{
	for (int i = 0; i < walls.size(); ++i)
	{
		removeChild(walls[i]->sprite);
		delete(walls[i]);
	}
	walls.clear();

	for (int i = 0; i < enemies.size(); ++i)
	{
		removeChild(enemiesSprites[i]->sprite);
		delete(enemiesSprites[i]);
		delete(enemies[i]);
	}
	enemies.clear();
	enemiesSprites.clear();



}

void GameScene::PauseGame(Ref *pSender)
{
	Director::getInstance()->getOpenGLView()->setCursorVisible(true);
	auto pauseScene = PauseScene::createScene();
	Director::getInstance()->pushScene(pauseScene);
}

void GameScene::BackToMenu(Ref *pSender)
{
	Director::getInstance()->getOpenGLView()->setCursorVisible(true);
	Director::getInstance()->popScene();
}