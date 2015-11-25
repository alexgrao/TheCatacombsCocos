#include "Laberynth.h"
#include "Vector2.h"
#include "Player.h"

USING_NS_CC;

bool Laberynth::isWall(int x, int y)
{
	if (labMatrix[x][y] == 1)
		return true;
	return false;
}

bool Laberynth::isWall(Vector2 vec)
{
	return isWall(vec.x, vec.y);
}

bool Laberynth::isIn(int x, int y)
{
	if (x < 0 || x > size.x-1) return false;
	if (y < 0 || y > size.y-1) return false;

	return true;
}

// Cargar laberintos diseñados
void Laberynth::Load(int catacomb, int level)
{
	switch (catacomb)
	{
	case 1:
		switch (level)
		{
		case 1:
			size.x = 9;
			size.y = 9;
			//Catacumba: 1, nivel: 1
			labMatrix = new int*[9];
			labMatrix[0] = {1, 1, 1, 1, 1, 1, 1, 1, 1 };

			labMatrix[1] = { 1, 0, 0, 0, 0, 0, 0, 0, 1 };

			labMatrix[2] = { 1, 0, 1, 1, 0, 1, 1, 0, 1 };

			labMatrix[3] = { 1, 1, 1, 1, 0, 1, 1, 0, 1 };

			labMatrix[4] = { 4, 0, 0, 0, 0, 1, 1, 0, 1 };

			labMatrix[5] = { 1, 1, 1, 1, 0, 0, 0, 0, 1 };

			labMatrix[6] = { 1, 0, 0, 1, 0, 1, 1, 0, 1 };

			labMatrix[7] = { 1, 0, 0, 1, 0, 0, 1, 0, 1 };

			labMatrix[8] = { 1, 1, 1, 1, 1, 1, 1, 5, 1 };


			break;
		}
		break;
	}

	findFields();
}

int Laberynth::field(int x, int y)
{
	return labMatrix[x][y];
}

Vector2* Laberynth::GetEntrance()
{
	return &Vector2(entrance.x, entrance.y);
}

Vector2* Laberynth::GetExit()
{
	return &Vector2(exit.x, exit.y);
}

Vector2* Laberynth::Size()
{
	return &Vector2(size.x, size.y);
}

void Laberynth::findFields()
{
	entrance.x = -1;
	entrance.y = -1;
	exit.x = -1;
	exit.y = -1;

	for (int i = 0; i < size.x; ++i)
	{
		if (field(i, 0) == 4)
		{
			entrance.x = i;
			entrance.y = 0;
		}
		if (field(i, 0) == 5)
		{
			exit.x = i;
			exit.y = 0;
		}
	}

	if (entrance.x == -1 || exit.x == -1)
	{
		for (int i = 0; i < size.y; ++i)
		{
			if (field(0, i) == 4)
			{
				entrance.x = 0;
				entrance.y = i;
			}
			if (field(0, i) == 5)
			{
				exit.x = 0;
				exit.y = i;
			}
		}

		if (entrance.x == -1 || exit.x == -1)
		{
			for (int i = 0; i < size.x; ++i)
			{
				if (field(i, size.y-1) == 4)
				{
					entrance.x = i;
					entrance.y = size.y - 1;
				}
				if (field(i, size.y - 1) == 5)
				{
					exit.x = i;
					exit.y = size.y - 1;
				}
			}

			if (entrance.x == -1 || exit.x == -1)
			{
				for (int i = 0; i < size.y; ++i)
				{
					if (field(size.x-1, i) == 4)
					{
						entrance.x = size.x - 1;
						entrance.y = i;
						break;
					}
					if (field(size.x - 1, i) == 5)
					{
						exit.x = size.x - 1;
						exit.y = i;
						break;
					}
				}
			}
		}
	}


}