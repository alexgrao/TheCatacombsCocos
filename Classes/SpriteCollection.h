#ifndef __SPRITE_COLLECTION_H__
#define __SPRITE_COLLECTION_H__

#include "cocos2d.h"
#include "Player.h"

USING_NS_CC;

class SpriteCollection
{
private:
	Sprite **sprites;
	int count = 0;
	int size = 2;
	void enlarge();

public:
	SpriteCollection();
	int Count();
	void AddSprite(Sprite*);
	void RemoveSprite(Sprite*);
	void Remove(int);
	Sprite* GetSprite(int);
	void Clear();
	Sprite* Last();


};

#endif