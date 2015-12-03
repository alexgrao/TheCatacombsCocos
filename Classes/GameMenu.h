#ifndef __GAME_MENU_H__
#define __GAME_MENU_H__

#include "cocos2d.h"
#include "CentSprite.h"

USING_NS_CC;

class GameMenu : public cocos2d::Layer
{
private:
	// debugg label
	Label* debugg;

	// Cities Red Balls
	CentSprite* Madrid;
	CentSprite* London;
	CentSprite* Rome;
	CentSprite* Berlin;
	int overCity = 0;
	int selectedCity = 0; // Madrid 1, London 2, Rome 3, Berlin 4   None 0
	void MarkCity(bool, int);

public:
	void Play(Ref *pSender);
	void BackToMainMenu(Ref *pSender);
	static cocos2d::Scene* createScene();
	void OnMouseMove(Event *event);
	void OnMouseDown(Event *event);

	/*static int Catacomb;
	static int Level;*/

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameMenu);
};

#endif // __GAME_SCENE_H__