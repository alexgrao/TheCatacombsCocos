#ifndef __SPRITE_ANIMATOR_H__
#define __SPRITE_ANIMATOR_H__

#include "CentSprite.h"
#include "CatacombTimer.h"

using namespace std;

class SpriteAnimator
{
private:
	CatacombTimer internalTimer;
	Texture2D** sprites;
	int nSprites;

	void UpdateSprite();
	void loadSprites(string);

	// Animación de movimiento
	float YFactor = 0;
	float XFactor = 0;
	float Yangle = 0;
	float Xangle = 0;
	float YSpeed = 1;
	float XSpeed = 1;
	Vector2F initialPosition;

public:
	SpriteAnimator(string, int, float);
	CentSprite* image;
	void AnimateAll(float delta);
	void AnimateSprites(float delta);
	void AnimateVibes(float delta);
	void DeleteEverything();

	// Animaciones de movimiento
	void SetXVibe(float, float, float);
	void SetYVibe(float, float, float);
	void SetPosition(float, float);
	void SetSize(float, float);
};

#endif