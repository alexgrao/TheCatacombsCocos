#ifndef __MYFUNCTIONS_H__
#define __MYFUNCTIONS_H__

#include "cocos2d.h"
#include "CentSprite.h"

class MyFunctions
{
public:
	static void SetSprite(cocos2d::Sprite*, float, float, float, float);
	static bool IsIn(int, int, CentSprite*);
};

#endif // __HELLOWORLD_SCENE_H__

