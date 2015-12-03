#include "SpriteAnimator.h"

SpriteAnimator::SpriteAnimator(string file, int numberOfSprites, float fps)
{
	nSprites = numberOfSprites;
	loadSprites(file);

	Sprite* sprite = new Sprite();
	sprite->initWithTexture(sprites[0]);
	image = new CentSprite(sprite, 0, 0, 0, 0);

	internalTimer = CatacombTimer(1 / fps);

	initialPosition = Vector2F(0, 0);
}

void SpriteAnimator::AnimateSprites(float delta)
{
	if (internalTimer.Check(delta))
	{
		// Si ya hemos llegado al último sprite
		if (internalTimer.GetCount() == nSprites)
		{
			float time = internalTimer.GetInterval() + internalTimer.GetTime();
			// Resetear temporizador
			internalTimer.Reset();
			internalTimer.Start();
			// dejarle el tiempo que tenía
			internalTimer.Check(time);
		}

		UpdateSprite();
	}
}

void SpriteAnimator::AnimateVibes(float delta)
{
	float newPosX = image->GetPosition().x;
	float newPosY = image->GetPosition().y;
	if (XFactor != 0)
	{
		newPosX += sin(Xangle) * XFactor;
		Xangle += delta * XSpeed;
		if (Xangle > M_PI * 2)
			Xangle = 0;
	}
	if (YFactor != 0)
	{
		newPosY += sin(Yangle) * YFactor;
		Yangle += delta * YSpeed;
		if (Yangle > M_PI * 2)
			Yangle = 0;
	}

	image->SetPosition(newPosX, newPosY);
}

void SpriteAnimator::AnimateAll(float delta)
{
	AnimateSprites(delta);
	AnimateVibes(delta);
}

void SpriteAnimator::UpdateSprite()
{
	image->sprite->setTexture(sprites[internalTimer.GetCount()-1]);
}

void SpriteAnimator::loadSprites(string path)
{
	sprites = new Texture2D*[nSprites];

	for (int i = 1; i <= nSprites; ++i)
	{
		string file = path + " (" + std::to_string(i) + ").png";

		Image* img = new Image();
		img->initWithImageFile(file);
		Texture2D* newTex = new Texture2D();
		newTex->initWithImage(img);

		sprites[i - 1] = newTex;
	}
}

void SpriteAnimator::DeleteEverything()
{
	delete(image->sprite);
	delete(image);
	for (int i = 0; i < nSprites; ++i)
		delete(sprites[i]);
	delete(sprites);
}

void SpriteAnimator::SetPosition(float x, float y)
{
	initialPosition.x = x;
	initialPosition.y = y;
	image->SetPosition(x + sin(Xangle) * XFactor, y + sin(Yangle) * YFactor);
}

void SpriteAnimator::SetSize(float width, float height)
{
	image->SetSize(width, height);
}

void SpriteAnimator::SetXVibe(float factor, float angle, float speed)
{
	XFactor = factor;
	Xangle = angle*M_PI / 180;
	XSpeed = speed;
}

void SpriteAnimator::SetYVibe(float factor, float angle, float speed)
{
	YFactor = factor;
	Yangle = angle*M_PI / 180;
	YSpeed = speed;
}