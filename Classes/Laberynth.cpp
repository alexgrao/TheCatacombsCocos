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

bool Laberynth::isExit(int x, int y)
{
	if (labMatrix[x][y] == 4)
		return true;
	return false;
}

bool Laberynth::isEntrance(int x, int y)
{
	if (labMatrix[x][y] == 3)
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

bool Laberynth::isMochila(int x, int y)
{
	if (labMatrix[x][y] == 2) return true;
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
	if (catacomb == 0 && level == 0)
	{
		//Catacumba: 1, nivel: 1
		size.x = 7;
		size.y = 7;
		labMatrix = new int*[7];
		labMatrix[0] = new int[7]{ 1, 1, 1, 1, 1, 1, 1 };

		labMatrix[1] = new int[7]{ 1, 0, 0, 1, 0, 0, 1 };

		labMatrix[2] = new int[7]{ 3, 0, 0, 0, 1, 0, 1 };

		labMatrix[3] = new int[7]{ 1, 0, 0, 1, 0, 0, 1 };

		labMatrix[4] = new int[7]{ 1, 0, 0, 0, 0, 0, 4 };

		labMatrix[5] = new int[7]{ 1, 0, 0, 0, 0, 0, 1 };

		labMatrix[6] = new int[7]{ 1, 1, 1, 1, 1, 1, 1 };

		findFields();

		return;
	}

	switch (catacomb)
	{
	case 1:
		switch (level)
		{
		case 1:
			//Catacumba: 1, nivel: 1
			size.x = 12;
			size.y = 12;
			labMatrix = new int*[12];
			labMatrix[0] = new int[12]{ 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

			labMatrix[1] = new int[12]{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 };

			labMatrix[2] = new int[12]{ 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1 };
<<<<<<< HEAD

			labMatrix[3] = new int[12]{ 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1 };

			labMatrix[4] = new int[12]{ 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1 };

			labMatrix[5] = new int[12]{ 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1 };

			labMatrix[6] = new int[12]{ 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1 };

			labMatrix[7] = new int[12]{ 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1 };

			labMatrix[8] = new int[12]{ 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1 };

			labMatrix[9] = new int[12]{ 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1 };

=======

			labMatrix[3] = new int[12]{ 1, 2, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1 };

			labMatrix[4] = new int[12]{ 1, 2, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1 };

			labMatrix[5] = new int[12]{ 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1 };

			labMatrix[6] = new int[12]{ 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1 };

			labMatrix[7] = new int[12]{ 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1 };

			labMatrix[8] = new int[12]{ 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1 };

			labMatrix[9] = new int[12]{ 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 2, 1 };

>>>>>>> origin/master
			labMatrix[10] = new int[12]{ 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1 };

			labMatrix[11] = new int[12]{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 1, 1 };


			break;

		case 2:
			//Catacumba: 1, nivel: 2
			size.x = 12;
			size.y = 12;
			labMatrix = new int*[12];
			labMatrix[0] = new int[12]{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1 };

			labMatrix[1] = new int[12]{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };

			labMatrix[2] = new int[12]{ 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1 };

			labMatrix[3] = new int[12]{ 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1 };

			labMatrix[4] = new int[12]{ 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1 };

			labMatrix[5] = new int[12]{ 1, 12, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1 };

			labMatrix[6] = new int[12]{ 1, 0, 1, 1, 1, 0, 1, 1, 11, 1, 0, 1 };

			labMatrix[7] = new int[12]{ 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1 };

			labMatrix[8] = new int[12]{ 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1 };

			labMatrix[9] = new int[12]{ 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1 };

			labMatrix[10] = new int[12]{ 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1 };

			labMatrix[11] = new int[12]{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 1, 1 };

			break;
<<<<<<< HEAD

		case 3:
			//Catacumba: 1, nivel: 3
			size.x = 14;
			size.y = 14;
			labMatrix = new int*[14];
			labMatrix[0] = new int[14]{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

			labMatrix[1] = new int[14]{ 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };

			labMatrix[2] = new int[14]{ 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1 };

			labMatrix[3] = new int[14]{ 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1 };

			labMatrix[4] = new int[14]{ 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1 };

			labMatrix[5] = new int[14]{ 1, 0, 1, 0, 1, 11, 1, 1, 0, 1, 13, 1, 0, 1 };

			labMatrix[6] = new int[14]{ 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1 };

			labMatrix[7] = new int[14]{ 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1 };

=======

		case 3:
			//Catacumba: 1, nivel: 3
			size.x = 14;
			size.y = 14;
			labMatrix = new int*[14];
			labMatrix[0] = new int[14]{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

			labMatrix[1] = new int[14]{ 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };

			labMatrix[2] = new int[14]{ 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1 };

			labMatrix[3] = new int[14]{ 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1 };

			labMatrix[4] = new int[14]{ 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1 };

			labMatrix[5] = new int[14]{ 1, 0, 1, 0, 1, 11, 1, 1, 0, 1, 13, 1, 0, 1 };

			labMatrix[6] = new int[14]{ 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1 };

			labMatrix[7] = new int[14]{ 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1 };

			labMatrix[8] = new int[14]{ 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1 };

			labMatrix[9] = new int[14]{ 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1 };

			labMatrix[10] = new int[14]{ 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1 };

			labMatrix[11] = new int[14]{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1 };

			labMatrix[12] = new int[14]{ 1, 0, 0, 0, 0, 0, 0, 14, 0, 0, 0, 0, 0, 1 };

			labMatrix[13] = new int[14]{ 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

			break;

		case 4:
			//Catacumba: 1, nivel: 4
			size.x = 14;
			size.y = 14;
			labMatrix = new int*[14];
			labMatrix[0] = new int[14]{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

			labMatrix[1] = new int[14]{ 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };

			labMatrix[2] = new int[14]{ 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1 };

			labMatrix[3] = new int[14]{ 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1 };

			labMatrix[4] = new int[14]{ 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1 };

			labMatrix[5] = new int[14]{ 1, 0, 1, 0, 1, 11, 1, 1, 0, 1, 0, 1, 14, 1 };

			labMatrix[6] = new int[14]{ 1, 0, 1, 0, 1, 0, 1, 1, 12, 1, 0, 1, 0, 1 };

			labMatrix[7] = new int[14]{ 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1 };

>>>>>>> origin/master
			labMatrix[8] = new int[14]{ 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1 };

			labMatrix[9] = new int[14]{ 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1 };

<<<<<<< HEAD
			labMatrix[10] = new int[14]{ 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1 };

			labMatrix[11] = new int[14]{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1 };

			labMatrix[12] = new int[14]{ 1, 0, 0, 0, 0, 0, 0, 14, 0, 0, 0, 0, 0, 1 };

			labMatrix[13] = new int[14]{ 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

			break;

		case 4:
			//Catacumba: 1, nivel: 4
			size.x = 14;
			size.y = 14;
			labMatrix = new int*[14];
			labMatrix[0] = new int[14]{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

			labMatrix[1] = new int[14]{ 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };

			labMatrix[2] = new int[14]{ 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1 };

			labMatrix[3] = new int[14]{ 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1 };

			labMatrix[4] = new int[14]{ 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1 };

			labMatrix[5] = new int[14]{ 1, 0, 1, 0, 1, 11, 1, 1, 0, 1, 0, 1, 14, 1 };

			labMatrix[6] = new int[14]{ 1, 0, 1, 0, 1, 0, 1, 1, 12, 1, 0, 1, 0, 1 };

			labMatrix[7] = new int[14]{ 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1 };

			labMatrix[8] = new int[14]{ 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1 };

			labMatrix[9] = new int[14]{ 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1 };

=======
>>>>>>> origin/master
			labMatrix[10] = new int[14]{ 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 4 };

			labMatrix[11] = new int[14]{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1 };

			labMatrix[12] = new int[14]{ 1, 0, 0, 0, 0, 0, 0, 13, 0, 0, 0, 0, 0, 1 };

			labMatrix[13] = new int[14]{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

			break;

		}

		break;

	case 2:

		switch (level)
		{
		case 1:
			//Catacumba: 2, nivel: 1
			size.x = 17;
			size.y = 17;
			labMatrix = new int*[17];
			labMatrix[0] = new int[17]{ 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

			labMatrix[1] = new int[17]{ 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1 };

			labMatrix[2] = new int[17]{ 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1 };

			labMatrix[3] = new int[17]{ 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1 };

			labMatrix[4] = new int[17]{ 1, 1, 14, 1, 0, 0, 0, 0, 1, 0, 0, 11, 0, 0, 0, 1, 1 };

			labMatrix[5] = new int[17]{ 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1 };

			labMatrix[6] = new int[17]{ 1, 0, 0, 1, 1, 13, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1 };

			labMatrix[7] = new int[17]{ 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1 };

			labMatrix[8] = new int[17]{ 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1 };

			labMatrix[9] = new int[17]{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1 };

			labMatrix[10] = new int[17]{ 1, 1, 1, 1, 1, 0, 1, 0, 1, 12, 0, 0, 0, 0, 1, 0, 1 };

			labMatrix[11] = new int[17]{ 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1 };

			labMatrix[12] = new int[17]{ 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };

			labMatrix[13] = new int[17]{ 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1 };

			labMatrix[14] = new int[17]{ 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1 };

			labMatrix[15] = new int[17]{ 1, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };

			labMatrix[16] = new int[17]{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1 };


			break;
		case 2:
			//Catacumba: 2, nivel: 2
			size.x = 17;
			size.y = 17;
			labMatrix = new int*[17];
			labMatrix[0] = new int[17]{ 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

			labMatrix[1] = new int[17]{ 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 2, 1 };

			labMatrix[2] = new int[17]{ 1, 1, 0, 1, 2, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1 };

			labMatrix[3] = new int[17]{ 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1 };

			labMatrix[4] = new int[17]{ 1, 1, 14, 1, 0, 0, 0, 0, 1, 0, 0, 11, 0, 0, 0, 1, 1 };

			labMatrix[5] = new int[17]{ 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1 };

			labMatrix[6] = new int[17]{ 1, 0, 0, 1, 1, 13, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1 };

			labMatrix[7] = new int[17]{ 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1 };

			labMatrix[8] = new int[17]{ 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1 };

			labMatrix[9] = new int[17]{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1 };

			labMatrix[10] = new int[17]{ 1, 1, 1, 1, 1, 0, 1, 0, 1, 12, 0, 0, 0, 0, 1, 0, 1 };

			labMatrix[11] = new int[17]{ 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1 };

			labMatrix[12] = new int[17]{ 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };

			labMatrix[13] = new int[17]{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1 };

			labMatrix[14] = new int[17]{ 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1 };

			labMatrix[15] = new int[17]{ 1, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 2, 1, 0, 0, 1 };

			labMatrix[16] = new int[17]{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 1, 1 };


			break;
		case 3:
			//Catacumba: 2, nivel: 3
			size.x = 20;
			size.y = 20;
			labMatrix = new int*[20];
			labMatrix[0] = new int[20]{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

			labMatrix[1] = new int[20]{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 1 };

			labMatrix[2] = new int[20]{ 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1 };

			labMatrix[3] = new int[20]{ 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1 };

			labMatrix[4] = new int[20]{ 1, 1, 1, 0, 1, 2, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 };

			labMatrix[5] = new int[20]{ 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1 };

			labMatrix[6] = new int[20]{ 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 2, 1, 1 };

			labMatrix[7] = new int[20]{ 4, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1 };

			labMatrix[8] = new int[20]{ 1, 0, 0, 0, 11, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1 };

			labMatrix[9] = new int[20]{ 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 13, 1, 1 };

			labMatrix[10] = new int[20]{ 1, 0, 0, 0, 0, 0, 1, 1, 12, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1 };

			labMatrix[11] = new int[20]{ 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1 };

			labMatrix[12] = new int[20]{ 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1 };

			labMatrix[13] = new int[20]{ 1, 1, 0, 1, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1 };

			labMatrix[14] = new int[20]{ 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1 };

			labMatrix[15] = new int[20]{ 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1 };

			labMatrix[16] = new int[20]{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 };

			labMatrix[17] = new int[20]{ 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1 };

			labMatrix[18] = new int[20]{ 1, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 };

			labMatrix[19] = new int[20]{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };


			break;
		case 4:
			//Catacumba: 2, nivel: 4
			size.x = 20;
			size.y = 20;
			labMatrix = new int*[20];
			labMatrix[0] = new int[20]{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

			labMatrix[1] = new int[20]{ 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 1 };

			labMatrix[2] = new int[20]{ 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1 };

			labMatrix[3] = new int[20]{ 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1 };

			labMatrix[4] = new int[20]{ 1, 1, 1, 0, 1, 2, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 };

			labMatrix[5] = new int[20]{ 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1 };

			labMatrix[6] = new int[20]{ 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 2, 1, 1 };

			labMatrix[7] = new int[20]{ 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1 };

			labMatrix[8] = new int[20]{ 1, 0, 0, 0, 11, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1 };

			labMatrix[9] = new int[20]{ 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 13, 1, 1 };

			labMatrix[10] = new int[20]{ 1, 0, 0, 0, 0, 0, 1, 1, 12, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1 };

			labMatrix[11] = new int[20]{ 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1 };

			labMatrix[12] = new int[20]{ 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1 };

			labMatrix[13] = new int[20]{ 1, 1, 0, 1, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1 };

			labMatrix[14] = new int[20]{ 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1 };

			labMatrix[15] = new int[20]{ 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1 };

			labMatrix[16] = new int[20]{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 };

			labMatrix[17] = new int[20]{ 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1 };

			labMatrix[18] = new int[20]{ 4, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 };

			labMatrix[19] = new int[20]{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };


			break;
		}

		break;
	}

	findFields();
}

void Laberynth::setField(int x, int y, int value) {
	labMatrix[x][y] = value;
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