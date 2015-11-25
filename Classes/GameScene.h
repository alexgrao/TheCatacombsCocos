#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "Laberynth.h"
#include "CentSprite.h"
#include "Enemy.h"
#include <vector>

USING_NS_CC;

class GameScene : public cocos2d::Layer
{
private:
	Label* debugg;
	Laberynth laberynth;
	//std::vector<Sprite*> walls;
	std::vector<CentSprite*> walls;
	Player player;
	Enemy enemy1;
	void findView();
	void updateView();
	void checkPlayerDirections();
	void checkEnemyDirections(Enemy);

public:
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);

	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

};

#endif // __HELLOWORLD_SCENE_H__

