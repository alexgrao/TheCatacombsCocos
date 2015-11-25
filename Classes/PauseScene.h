#ifndef __PAUSE_SCENE_H__
#define __PAUSE_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class PauseScene : public cocos2d::Layer
{
public:
	void ResumeGame(Ref *pSender);
	void GoToGameMenu(Ref *pSender);
	static cocos2d::Scene* createScene();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(PauseScene);
};

#endif // __PAUSE_SCENE_H__
