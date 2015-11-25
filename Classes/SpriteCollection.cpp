#include "SpriteCollection.h"

USING_NS_CC;

SpriteCollection::SpriteCollection()
{
	sprites = new Sprite*[2];
}

void SpriteCollection::enlarge()
{
	/*size *= 2;
	Sprite **newSprites = new Sprite*[size];
	for (int i = 0; i < count; ++i)
	{
		newSprites[i] = sprites[i];
	}
	delete[] sprites;
	sprites = newSprites;*/

	Sprite ** buffer = sprites;
	size *= 2;
	sprites = new Sprite*[size];

	for (int i = 0; i < count; ++i)
	{
		sprites[i] = buffer[i];
	}

	delete[] buffer;
}

int SpriteCollection::Count() { return count; }

void SpriteCollection::AddSprite(Sprite *sprite)
{
	if (count == size)
		enlarge();
	sprites[count] = sprite;
	++count;

	for (int i = 0; i < count;++i)
		sprites[i]->getScale();
}

void SpriteCollection::RemoveSprite(Sprite *sprite)
{
	for (int i = 0; i < count; ++i)
	{
		if (sprites[i] == sprite)
			Remove(i);
	}
}

void SpriteCollection::Remove(int n)
{
	delete sprites[n];
	for (int i = n+1; i < count; ++i)
	{
		sprites[i - 1] = sprites[i];
	}
	--count;
}

Sprite* SpriteCollection::GetSprite(int i)
{
	return sprites[i];
}

void SpriteCollection::Clear()
{
	for (int i = 0; i < count; ++i)
		delete sprites[i];

	count = 0;
}

Sprite* SpriteCollection::Last() { return sprites[count - 1]; }