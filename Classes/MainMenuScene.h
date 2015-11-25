#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"
#include "CentSprite.h"

USING_NS_CC;

class MainMenuScene : public cocos2d::Layer
{
public:
	Label* debugg;
	void Play(Ref *pSender);
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuScene);
};

#endif // __HELLOWORLD_SCENE_H__
