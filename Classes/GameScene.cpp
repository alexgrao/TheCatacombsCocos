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
#include "CatacombTimer.h"
#include "Player.h"
#include "SimpleAudioEngine.h"

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

	laberynth.Load(catacomb, level);

	loadPlayer();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//auto audio = SimpleAudioEngine::getInstance();

	// KEY EVENT FOR MOVING
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	findEnemies();
	// DEBUGG MOCHILA 
	debugg = Label::createWithTTF(
	"Bateria: " + std::to_string(player.GetBattery()) 
	+ " Bengalas(R-B-G-Y): " + std::to_string(player.BengalasCount(0))  
	+ std::to_string(player.BengalasCount(1))
	+ std::to_string(player.BengalasCount(2))
	+ std::to_string(player.BengalasCount(3))
	+ " Balas(1-2-3-4): " + std::to_string(player.BulletsCount(0)) + std::to_string(player.BulletsCount(1)) + std::to_string(player.BulletsCount(2)) + std::to_string(player.BulletsCount(3))
	, "fonts/Marker Felt.ttf", 15);
	debugg->setPosition(Point(visibleSize.width * 0.5, visibleSize.height*0.1));
	debugg->setColor(ccc3(255, 0, 0));
	this->addChild(debugg, 20);

	// DEBUGG LABEL
	//debugg = Label::createWithTTF("Tiempo: 0", "fonts/Marker Felt.ttf", 15);
	//debugg->setPosition(Point(visibleSize.width * 0.6, visibleSize.height*0.6));
	//debugg->setColor(ccc3(255, 0, 0));
	//this->addChild(debugg, 20);

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

	lanternShadow = Sprite::create(Assets::LanternShadow);
	//lanternShadow->setOpacity(240);
	lanternShadow->setOpacity(0);
	addChild(lanternShadow, 15);

	// MOUSE EVENT FOR CROSS
	auto listenerMouse = EventListenerMouse::create();
	listenerMouse->onMouseMove = CC_CALLBACK_1(GameScene::OnMouseMove, this);
	listenerMouse->onMouseDown = CC_CALLBACK_1(GameScene::OnMouseDown, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerMouse, this);

	animatorTimer = CatacombTimer(0.75);

	hands = new SpriteAnimator("animations/hands/hands", 28, 30);
	hands->image->SetSize(103, 60);
	hands->SetYVibe(0.01, 0, 5);
	addChild(hands->image->sprite, 20);

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

				CentSprite* cs = new CentSprite(e->GetSprite(), 0, 0, 0, 0);
				e->sprite = cs;
				addChild(cs->sprite);
			}
		}
	}
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{
	switch (keyCode)
	{
<<<<<<< HEAD
	case EventKeyboard::KeyCode::KEY_W:
		WPressed = true;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		SPressed = true;
=======
	case EventKeyboard::KeyCode::KEY_W :
		if (player.canForward)
		{
			player.stepForward();
			updateView();
			checkPlayerDirections();
			CheckWin();
			CheckMochila();
			CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(1.0);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/ButtonClick.wav");
		}
		break;
	case EventKeyboard::KeyCode::KEY_S:
		if (player.canBackward)
		{
			player.stepBackward();
			updateView();
			checkPlayerDirections();
			CheckWin();
			CheckMochila();
			CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(1.0);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/ButtonClick.wav");
		}
>>>>>>> origin/master
		break;
	case EventKeyboard::KeyCode::KEY_A:
		player.turnLeft();
		updateView();
		checkPlayerDirections();
		CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(1.0);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/ButtonClick.wav");
		break;
	case EventKeyboard::KeyCode::KEY_D:
		player.turnRight();
		updateView();
		checkPlayerDirections();
		CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(1.0);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/ButtonClick.wav");
		break;
	}

	switch(keyCode)
	{
		case EventKeyboard::KeyCode::KEY_ESCAPE:
			PauseGame(this);
			break;
	}
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
		WPressed = false;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		SPressed = false;
		break;
	}
}

void GameScene::checkKeys()
{
	if (WPressed)
	{
		if (player.canForward)
		{
			player.stepForward();
			//updateView();
			moving = 1;
			CalculateWallAnimations();
			checkPlayerDirections();
			CheckWin();
		}
	}
	else if (SPressed)
	{
		if (player.canBackward)
		{
			player.stepBackward();
			//updateView();
			moving = -1;
			CalculateWallAnimations();
			checkPlayerDirections();
			CheckWin();
		}
	}
}

void GameScene::checkPlayerDirections()
{
	int x = player.Position.x + player.Direction.x;
	int y = player.Position.y + player.Direction.y;
	if (laberynth.isIn(x, y) && !laberynth.isWall(x, y) && !laberynth.isEntrance(x,y) /* && !laberynth.isExitEntrance(x,y)*/)
		player.canForward = true;
	else
		player.canForward = false;

	x = player.Position.x - player.Direction.x;
	y = player.Position.y - player.Direction.y;
	if (laberynth.isIn(x, y) && !laberynth.isWall(x, y) && !laberynth.isEntrance(x, y)/*&& !laberynth.isExitEntrance(x, y)*/)
		player.canBackward = true;
	else
		player.canBackward = false;
}

void GameScene::findView()
{
	walls.clear();

	bool avoidLeft = false, avoidRight = false;

	int x = player.Position.x;
	int y = player.Position.y;

	float posX, posY, width, height;
<<<<<<< HEAD

	for (int nivel = 0; nivel < 4; ++nivel)
	{
		x += player.Direction.x;
		y += player.Direction.y;

		if (!laberynth.isIn(x, y)) return;


		CentSprite* shadow = new CentSprite(Assets::Shadow, 0, Assets::ShadowsParams[nivel][0], 100, Assets::ShadowsParams[nivel][1], 6 - nivel);
		walls.push_back(shadow);
		shadow->SetOpacity(Assets::ShadowsParams[nivel][2]);
		walls[walls.size() - 1]->Tag = "ShadowFront";
=======

	for (int nivel = 0; nivel < 4; ++nivel)
	{
		x += player.Direction.x;
		y += player.Direction.y;

		if (!laberynth.isIn(x, y)) return;
>>>>>>> origin/master

		////////////////////////////////////////////////////////////////// LATERALES FRONTALES
		if (nivel > 0) // Solo para los niveles 2-4
		{
			if (!avoidLeft)
			{
				// Pared frontal izquierda
				if (laberynth.isWall(x + player.Left.x, y + player.Left.y))
				{
					posX = Assets::LeftWallParams[nivel][0];
					posY = Assets::LeftWallParams[nivel][1];
					width = Assets::LeftWallParams[nivel][2];
					height = Assets::LeftWallParams[nivel][3];
					walls.push_back(new CentSprite(Assets::Wall, posX, posY, width, height, 6-nivel));
<<<<<<< HEAD
					walls[walls.size() - 1]->Tag = "LeftFrontal";
				}
			}

			if (!avoidRight)
			{
				// Pared frontal derecha
				if (laberynth.isWall(x - player.Left.x, y - player.Left.y))
				{
					posX = Assets::RightWallParams[nivel][0];
					posY = Assets::RightWallParams[nivel][1];
					width = Assets::RightWallParams[nivel][2];
					height = Assets::RightWallParams[nivel][3];
					walls.push_back(new CentSprite(Assets::Wall, posX, posY, width, height, 6-nivel));
					walls[walls.size() - 1]->Tag = "RightFrontal";
				}
			}

			avoidLeft = avoidRight = false;
		}

		///////////////////////////////////// FRONTAL

		if (laberynth.isWall(x, y))
		{
			posX = Assets::FrontWallsParams[nivel][0];
			posY = Assets::FrontWallsParams[nivel][1];
			width = Assets::FrontWallsParams[nivel][2];
			height = Assets::FrontWallsParams[nivel][3];
			walls.push_back(new CentSprite(Assets::Wall, posX, posY, width, height, 6 - nivel));
			walls[walls.size() - 1]->Tag = "Frontal";
		}

		///////////////////////////////////// LATERALES EN PERSPECTIVA
		else
		{
			// IZQUIERDA
			if (laberynth.isWall(x + player.Left.x, y + player.Left.y))
			{
				avoidLeft = true;

				posX = Assets::Left3DWallParams[nivel][0];
				posY = Assets::Left3DWallParams[nivel][1];
				width = Assets::Left3DWallParams[nivel][2];
				height = Assets::Left3DWallParams[nivel][3];

				walls.push_back(new CentSprite(Assets::ShadowOverWall, posX, posY, width, height, 6 - nivel));
				walls[walls.size() - 1]->Tag = "Left3DShadow";
				walls[walls.size() - 1]->SetOpacity(150);
				walls.push_back(new CentSprite(Assets::Wall3D, posX, posY, width, height, 6-nivel));
				walls[walls.size() - 1]->Tag = "Left3D";
			}
			//DERECHA
			if (laberynth.isWall(x - player.Left.x, y - player.Left.y))
			{
				avoidRight = true;

				posX = Assets::Right3DWallParams[nivel][0];
				posY = Assets::Right3DWallParams[nivel][1];
				width = Assets::Right3DWallParams[nivel][2];
				height = Assets::Right3DWallParams[nivel][3];

				walls.push_back(new CentSprite(Assets::ShadowOverWall, posX, posY, width, height, 6-nivel));
				walls[walls.size() - 1]->Tag = "Right3DShadow";
				walls[walls.size() - 1]->SetOpacity(150);
				walls.push_back(new CentSprite(Assets::Wall3D, posX, posY, width, height, 6-nivel));
				walls[walls.size() - 1]->Tag = "Right3D";
			}
		}
=======
				}
			}

			if (!avoidRight)
			{
				// Pared frontal derecha
				if (laberynth.isWall(x - player.Left.x, y - player.Left.y))
				{
					posX = Assets::RightWallParams[nivel][0];
					posY = Assets::RightWallParams[nivel][1];
					width = Assets::RightWallParams[nivel][2];
					height = Assets::RightWallParams[nivel][3];
					walls.push_back(new CentSprite(Assets::Wall, posX, posY, width, height, 6-nivel));
				}
			}

			avoidLeft = avoidRight = false;
		}

		///////////////////////////////////// FRONTAL

		if (laberynth.isWall(x, y))
		{
			posX = Assets::FrontWallsParams[nivel][0];
			posY = Assets::FrontWallsParams[nivel][1];
			width = Assets::FrontWallsParams[nivel][2];
			height = Assets::FrontWallsParams[nivel][3];
			walls.push_back(new CentSprite(Assets::Wall, posX, posY, width, height, 6 - nivel));
		}

		///////////////////////////////////// LATERALES EN PERSPECTIVA
		else
		{
			// IZQUIERDA
			if (laberynth.isWall(x + player.Left.x, y + player.Left.y))
			{
				avoidLeft = true;

				posX = Assets::Left3DWallParams[nivel][0];
				posY = Assets::Left3DWallParams[nivel][1];
				width = Assets::Left3DWallParams[nivel][2];
				height = Assets::Left3DWallParams[nivel][3];

				walls.push_back(new CentSprite(Assets::ShadowOverWall, posX, posY, width, height, 5 - nivel));
				walls[walls.size() - 1]->SetOpacity(150);
				walls.push_back(new CentSprite(Assets::Wall3D, posX, posY, width, height, 5-nivel));
			}
			//DERECHA
			if (laberynth.isWall(x - player.Left.x, y - player.Left.y))
			{
				avoidRight = true;

				posX = Assets::Right3DWallParams[nivel][0];
				posY = Assets::Right3DWallParams[nivel][1];
				width = Assets::Right3DWallParams[nivel][2];
				height = Assets::Right3DWallParams[nivel][3];

				walls.push_back(new CentSprite(Assets::ShadowOverWall, posX, posY, width, height, 5-nivel));
				walls[walls.size() - 1]->SetOpacity(150);
				walls.push_back(new CentSprite(Assets::Wall3D, posX, posY, width, height, 5-nivel));
			}
		}

		CentSprite* shadow = new CentSprite(Assets::Shadow, 0, Assets::ShadowsParams[nivel][0], 100, Assets::ShadowsParams[nivel][1], 6-nivel);
		walls.push_back(shadow);
		shadow->SetOpacity(Assets::ShadowsParams[nivel][2]);
>>>>>>> origin/master

	}
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
		e->SetVisible(false);
		return;
	}

	// si el jugador mira en dirección contraria
	if (distanceFrontal > 0 && sense > 0)
	{
		e->SetVisible(false);
		return;
	}
	if (distanceFrontal < 0 && sense < 0)
	{
		e->SetVisible(false);
		return;
	}

	if (distanceFrontal < 0) distanceFrontal *= -1;

	// si está demasiado lejos
	if (distanceFrontal > 4)
	{
		e->SetVisible(false);
		return;
	}
	if (distanceFrontal < 0)
	{
		e->SetVisible(false);
		return;
	}

	e->SetVisible(true);

	if (e->DistanceToCamera().x > distanceFrontal)
		e->sprite->SetOrderZ(7 - distanceFrontal);
	else
		e->sprite->SetOrderZ(7 - e->DistanceToCamera().x);

	if (distanceFrontal != 0)
		e->SetDistanceToCamera(distanceFrontal, distanceLateral + 2);
}

void GameScene::updateView()
{
	wallAnimators.clear();

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

	hands->AnimateVibes(delta);

	if (moving != 0)
	{
		AnimateWalls(delta);
		hands->AnimateSprites(delta);
	}
	else
		checkKeys();

	for (int i = 0; i < enemies.size(); ++i)
	{
		Enemy* e = enemies[i];
		if (e->GetLifes() > 0)
		{
			if (e->CheckTimer(delta))
			{
				Vector2 prev = e->Position.Copy();
				e->whereIgo(&laberynth);
				e->stepForward();
				laberynth.MoveEnemy(prev.x, prev.y, e->Position.x, e->Position.y);
				findEnemyView(i);
			}

			if (e->IsVisible()) e->UpdateSprite();
<<<<<<< HEAD
=======

>>>>>>> origin/master
		}
	}
	debugg->setString("Bateria: " + std::to_string(player.GetBattery())
		+ " Bengalas(R-B-G-Y): " + std::to_string(player.BengalasCount(0))
		+ std::to_string(player.BengalasCount(1))
		+ std::to_string(player.BengalasCount(2))
		+ std::to_string(player.BengalasCount(3))
		+ " Balas(1-2-3-4): " + std::to_string(player.BulletsCount(0)) + std::to_string(player.BulletsCount(1)) + std::to_string(player.BulletsCount(2)) + std::to_string(player.BulletsCount(3)));

	// cross movement

	cross->setPosition(Vec2(mousePosition.x + recoil.x, mousePosition.y + recoil.y));
	lanternShadow->setPosition(Vec2(mousePosition.x + recoil.x, mousePosition.y + recoil.y));
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

	for (int i = 0; i < enemies.size(); ++i)
	{
		Enemy* e = enemies[i];
		if (e->sprite->GetPosition().x < 0) continue;

		if (MyFunctions::IsIn(x, y, e->sprite))
		{
			if (e->Damage())
			{
				laberynth.Set(e->Position.x, e->Position.y, 0);
				e->sprite->SetPosition(-100, -100);
				removeChild(e->sprite->sprite);
			}
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
		removeChild(enemies[i]->sprite->sprite);
		delete(enemies[i]->sprite);
		delete(enemies[i]);
	}
	enemies.clear();

	removeChild(hands->image->sprite);
	hands->DeleteEverything();
	delete(hands);

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

void GameScene::CheckWin()
{
	if (!laberynth.isExit(player.Position.x, player.Position.y)) return;

	BackToMenu(this);
}

<<<<<<< HEAD
void GameScene::AnimateWalls(float delta)
{
	// Si ya ha terminado
	if (animatorTimer.Check(delta))
	{
		animatorTimer.Restart();
		updateView();
		moving = 0;
		return;
	}

	for (int i = 0; i < wallAnimators.size(); ++i)
	{
		WallAnimator anim = wallAnimators[i];

		anim.Animate(animatorTimer.GetPercentageFull());
	}
}

void GameScene::CalculateWallAnimations()
{
	for (int i = 0; i < walls.size(); ++i)
	{
		CentSprite* cs = walls[i];

		/*if (cs->Tag == "Left3DShadow" || cs->Tag == "Right3DShadow" || cs->Tag == "ShadowFront")
			continue;*/

		int nextDistance = (6 - cs->sprite->getZOrder()) - moving;

		WallAnimator anim = WallAnimator(cs);
		anim.SetOrigin(cs->GetPosition().x, cs->GetPosition().y, cs->GetSize().x, cs->GetSize().y);

		if (cs->Tag == "Frontal")
		{
			if (nextDistance < 0)
				anim.SetDestiny(0,0,100,100);
			else if (nextDistance > 3)
				anim.SetDestiny(39, 40, 29, 9);
			else
				anim.SetDestiny(Assets::FrontWallsParams[nextDistance]);
		}
		else if (cs->Tag == "LeftFrontal")
		{
			if (nextDistance < 1)
				anim.SetDestiny(-100, 0, 100, 100);
			else if (nextDistance > 3)
				anim.SetDestiny(3, 40, 29, 9);
			else
				anim.SetDestiny(Assets::LeftWallParams[nextDistance]);
		}
		else if (cs->Tag == "RightFrontal")
		{
			if (nextDistance < 1)
				anim.SetDestiny(100, 0, 100, 100);
			else if (nextDistance > 3)
				anim.SetDestiny(45, 40, 29, 9);
			else
				anim.SetDestiny(Assets::RightWallParams[nextDistance]);
		}
		else if (cs->Tag == "Left3D" )
		{
			if (nextDistance < 0)
				anim.SetDestiny(10, -43.5, -40, 195);
			else if (nextDistance > 3)
				anim.SetDestiny(44, 40, -1.25, 10);
			else
				anim.SetDestiny(Assets::Left3DWallParams[nextDistance]);
		}
		else if (cs->Tag == "Right3D")
		{
			if (nextDistance < 0)
				anim.SetDestiny(103, -43.5, 40, 195);
			else if (nextDistance > 3)
				anim.SetDestiny(44, 40, 1.25, 10);
			else
				anim.SetDestiny(Assets::Right3DWallParams[nextDistance]);
		}
		else if (cs->Tag == "ShadowFront")
		{
			int newOpacity = 0;
			if (nextDistance > 3) newOpacity = 255;
			else if (nextDistance > 0) newOpacity = Assets::ShadowsParams[nextDistance][2];
			anim.SetDestiny(0, Assets::ShadowsParams[nextDistance][0], 100, Assets::ShadowsParams[nextDistance][1], newOpacity);
		}
		else if (cs->Tag == "Left3DShadow")
		{
			if (nextDistance < 0)
				anim.SetDestiny(10, -43.5, -40, 195, 0);
			else if (nextDistance > 3)
				anim.SetDestiny(44, 40, -1.25, 10, 255);
			else
				anim.SetDestiny(Assets::Left3DWallParams[nextDistance], Assets::ShadowsParams[nextDistance][2]);

		}
		else if (cs->Tag == "Right3DShadow")
		{
			if (nextDistance < 0)
				anim.SetDestiny(103, -43.5, 40, 195, 0);
			else if (nextDistance > 3)
				anim.SetDestiny(44, 40, 1.25, 10, 255);
			else
				anim.SetDestiny(Assets::Right3DWallParams[nextDistance], Assets::ShadowsParams[nextDistance][2]);
		}

		wallAnimators.push_back(anim);
=======
void GameScene::CheckMochila()
{
	if (laberynth.isMochila(player.Position.x, player.Position.y)) {
		player.GenerarObjetos(p);
		laberynth.setField(player.Position.x, player.Position.y,0);
>>>>>>> origin/master
	}
}