#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "Laberynth.h"
#include "CentSprite.h"
#include "Enemy.h"
#include "Vector2F.h"
#include <vector>

USING_NS_CC;

class GameScene : public cocos2d::Layer
{
private:
	int catacomb = 1;
	int level = 1;

	Label* debugg;
	Laberynth laberynth;

	// PlayerControl
	Player player;
	void checkPlayerDirections();
	void loadPlayer();

	// for weapon
	Sprite* cross;
	Vector2F recoil;
	Vector2F mousePosition;
	Vector2F delta;
	Sprite* lanternShadow;
	
	// Graphics
	std::vector<CentSprite*> walls;
	void findView();
	void findEnemyView(int);
	void updateView();
	void DeleteEverything();

	// Enemies
	void findEnemies();
	std::vector<Enemy*> enemies;
	void checkPressedOnEnemies(int, int);

	// System
	float time; // tiempo desde que empezamos el juego en segundos
	int ejemplo[5];

public:
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
	void OnMouseMove(Event *event);
	void OnMouseDown(Event *event);
	void PauseGame(Ref *pSender);
	void BackToMenu(Ref *pSender);

	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

	void update(float) override;

};

#endif // __HELLOWORLD_SCENE_H__

