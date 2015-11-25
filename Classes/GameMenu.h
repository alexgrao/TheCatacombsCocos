#ifndef __GAME_MENU_H__
#define __GAME_MENU_H__

#include "cocos2d.h"

USING_NS_CC;

class GameMenu : public cocos2d::Layer
{
public:
	void Play(Ref *pSender);
	void BackToMainMenu(Ref *pSender);
	static cocos2d::Scene* createScene();

	/*static int Catacomb;
	static int Level;*/

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameMenu);
};

#endif // __GAME_SCENE_H__