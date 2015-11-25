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

bool Laberynth::isExitEntrance(int x, int y)
{
	if (labMatrix[x][y] == 3 || labMatrix[x][y] == 4)
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

bool Laberynth::isEnemy(int x, int y)
{
	if (labMatrix[x][y] >= 10)
		return true;
	return false;
}

int Laberynth::Get(int x, int y)
{
	return labMatrix[x][y];
}

void Laberynth::Set(int x, int y, int n)
{
	labMatrix[x][y] = n;
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
			//Catacumba: 1, nivel: 1
			size.x = 8;
			size.y = 8;
			labMatrix = new int*[8];
			labMatrix[0] = new int[8]{ 1, 1, 1, 1, 1, 3, 1, 1 };

			labMatrix[1] = new int[8]{ 1, 0, 0, 0, 1, 0, 1, 1 };

			labMatrix[2] = new int[8]{ 1, 0, 1, 0, 1, 0, 1, 1 };

			labMatrix[3] = new int[8]{ 1, 0, 1, 0, 1, 0, 1, 1 };

			labMatrix[4] = new int[8]{ 1, 0, 1, 0, 0, 0, 0, 1 };

			labMatrix[5] = new int[8]{ 4, 0, 1, 0, 1, 11, 1, 1 };

			labMatrix[6] = new int[8]{ 1, 1, 0, 0, 1, 0, 1, 1 };

			labMatrix[7] = new int[8]{ 1, 1, 1, 1, 1, 1, 1, 1 };

			break;

		case 2:
			//Catacumba: 1, nivel: 2
			size.x = 10;
			size.y = 10;
			labMatrix = new int*[10];
			labMatrix[0] = new int[10]{ 1, 1, 1, 1, 1, 1, 3, 1, 1, 1 };

			labMatrix[1] = new int[10]{ 1, 1, 1, 1, 1, 1, 0, 1, 0, 1 };

			labMatrix[2] = new int[10]{ 1, 1, 0, 1, 1, 1, 0, 1, 0, 1 };

			labMatrix[3] = new int[10]{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 1 };

			labMatrix[4] = new int[10]{ 1, 1, 1, 1, 1, 1, 0, 1, 1, 1 };

			labMatrix[5] = new int[10]{ 1, 1, 1, 1, 1, 1, 0, 1, 1, 1 };

			labMatrix[6] = new int[10]{ 1, 0, 1, 1, 0, 0, 0, 1, 1, 1 };

			labMatrix[7] = new int[10]{ 4, 0, 1, 1, 0, 1, 0, 0, 0, 1 };

			labMatrix[8] = new int[10]{ 1, 0, 0, 0, 0, 1, 1, 1, 1, 1 };

			labMatrix[9] = new int[10]{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };


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
		if (field(i, 0) == 3)
		{
			entrance.x = i;
			entrance.y = 0;
		}
		if (field(i, 0) == 4)
		{
			exit.x = i;
			exit.y = 0;
		}
	}

	if (entrance.x == -1 || exit.x == -1)
	{
		for (int i = 0; i < size.y; ++i)
		{
			if (field(0, i) == 3)
			{
				entrance.x = 0;
				entrance.y = i;
			}
			if (field(0, i) == 4)
			{
				exit.x = 0;
				exit.y = i;
			}
		}

		if (entrance.x == -1 || exit.x == -1)
		{
			for (int i = 0; i < size.x; ++i)
			{
				if (field(i, size.y-1) == 3)
				{
					entrance.x = i;
					entrance.y = size.y - 1;
				}
				if (field(i, size.y - 1) == 4)
				{
					exit.x = i;
					exit.y = size.y - 1;
				}
			}

			if (entrance.x == -1 || exit.x == -1)
			{
				for (int i = 0; i < size.y; ++i)
				{
					if (field(size.x-1, i) == 3)
					{
						entrance.x = size.x - 1;
						entrance.y = i;
						break;
					}
					if (field(size.x - 1, i) == 4)
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

void Laberynth::MoveEnemy(int oldx, int oldy, int newx, int newy)
{
	if (isEnemy(oldx, oldy))
	{
		int enemyNumber = labMatrix[oldx][oldy];

		labMatrix[oldx][oldy] = 0;
		labMatrix[newx][newy] = enemyNumber;

	}
}