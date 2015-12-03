#include "Enemy.h"
#include "Laberynth.h"
#include "cocos2d.h"
#include "Assets.h"
#include <time.h>
#include <cstdlib>

USING_NS_CC;

Enemy::Enemy(void)
{
	InitVectors();
}

Enemy::Enemy(int x, int y, int vidas, int rango, float duracion)
{
	InitVectors();

	Position.x = x;
	Position.y = y;
	lifes = vidas;
	range = rango;
	timer = CatacombTimer(duracion);
}

Enemy::Enemy(int id)
{
	InitVectors();
	Load(id);
}

void Enemy::turnLeft()
{
	int x = -Direction.x;
	int y = -Direction.y;
	Direction.x = Left.x;
	Direction.y = Left.y;
	Left.x = x;
	Left.y = y;
}

void Enemy::turnRight()
{
	int x = -Left.x;
	int y = -Left.y;
	Left.x = Direction.x;
	Left.y = Direction.y;
	Direction.x = x;
	Direction.y = y;
}

void Enemy::stepForward()
{
	Position.x += Direction.x;
	Position.y += Direction.y;
}

void Enemy::stepBackward()
{
	Position.x -= Direction.x;
	Position.y -= Direction.y;
}

void Enemy::whereIgo(Laberynth* lab)
{
	int direcciones_posibles = 0;
	int x, y;
	bool canForward = false, canLeft = false, canRight = false;

	int distanceX;
	int distanceY;

	// comprobar izquierda
	x = Position.x + Left.x;
	y = Position.y + Left.y;

	distanceX = initialPosition.x - x;
	if (distanceX < 0) distanceX *= -1;
	distanceY = initialPosition.y - y;
	if (distanceY < 0) distanceY *= -1;

	if (lab->isIn(x, y) && !lab->isWall(x, y) && distanceX <= range && distanceY <= range)
	{
		++direcciones_posibles;
		canLeft = true;
	}

	// comprobar derecha
	x = Position.x - Left.x;
	y = Position.y - Left.y;

	distanceX = initialPosition.x - x;
	if (distanceX < 0) distanceX *= -1;
	distanceY = initialPosition.y - y;
	if (distanceY < 0) distanceY *= -1;

	if (lab->isIn(x, y) && !lab->isWall(x, y) && distanceX <= range && distanceY <= range)
	{
		++direcciones_posibles;
		canRight = true;
	}

	// comprobar delante
	x = Position.x + Direction.x;
	y = Position.y + Direction.y;

	distanceX = initialPosition.x - x;
	if (distanceX < 0) distanceX *= -1;
	distanceY = initialPosition.y - y;
	if (distanceY < 0) distanceY *= -1;

	if (lab->isIn(x, y) && !lab->isWall(x, y) && distanceX <= range && distanceY <= range)
	{
		++direcciones_posibles;
		canForward = true;
	}

	// Si no puede avanzar en ninguna dirección, darse la vuelta
	if (direcciones_posibles == 0) Direction = Vector2(-Direction.x, -Direction.y);

	// Si puede ir hacia alguna dirección
	else
	{
		float probabilidad = 100 / direcciones_posibles;
		int random = 0;

		if (canLeft) // si puede ir a la izquierda;
		{
			srand(time(NULL));
			random = rand() % 101; // numero entre 0 y 100;
			// Si el aleatorio supera la probabilidad, o es que no hay más direcciones posibles
			if (random <= probabilidad || direcciones_posibles == 1)
			{
				// gira a la izquierda y termina
				turnLeft();
				return;
			}
		}
		if (canRight)
		{
			srand(time(NULL));
			random = rand() % 101; 

			if (random <= probabilidad || (!canLeft && direcciones_posibles == 1) || (canLeft && direcciones_posibles == 2))
			{
				turnRight();
				return;
			}
		}
		
		// Aquí no hace falta hacer nada. Si llegamos a este punto significa que sí que podemos ir hacia adelante, (ya que de lo contrario
		// anteriormente habría detectado que no hay más direcciones posiblesy habría tirado para la izquierda o para la derecha, y si no
		// pudiera ir ni lados ni adelante se habría dado la vuelta. Por lo tanto, si el código llega hasta aquí es porque puede ir hacia
		// adelante y no se ha ido ni a la izquierda ni a la derecha). Lo único que hay que hacer es dejar la dirección que ya tiene.
	}
}

bool Enemy::CheckTimer(float delta)
{
	return timer.Check(delta);
}

void Enemy::Load(int id)
{
	ID = id;

	switch (id)
	{
	case 1:
		timer = CatacombTimer(1.5);
		lifes = 3;
		imageSprite = Assets::Rat;
		range = 1;
		channel = 0;

		SetScreenPositions(id);

		break;

	default:
		Load(1);

	}
}

const char* Enemy::GetSprite()
{
	return imageSprite;
}

void Enemy::SearchInitialDirection(Laberynth* lab)
{
	Direction.x = 1;
	Direction.y = 0;

	int x = Position.x + Direction.x;
	int y = Position.y + Direction.y;

	if (lab->isIn(x,y) && !lab->isWall(x, y))
	{
		Left.x = 0;
		Left.y = -1;
		return;
	}

	Direction.x = -1;
	Direction.y = 0;

	x = Position.x + Direction.x;
	y = Position.y + Direction.y;

	if (lab->isIn(x, y) && !lab->isWall(x,y))
	{
		Left.x = 0;
		Left.y = 1;
		return;
	}

	Direction.x = 0;
	Direction.y = 1;

	x = Position.x + Direction.x;
	y = Position.y + Direction.y;

	if (lab->isIn(x, y) && !lab->isWall(x,y))
	{
		Left.x = -1;
		Left.y = 0;
		return;
	}

	Direction.x = 0;
	Direction.y = -1;
	Left.x = 1;
	Left.y = 0;
}

double Enemy::GetTime() { return timer.GetTime(); }

Vector2 Enemy::GetInitialPosition() { return initialPosition.Copy(); }

void Enemy::SetPosition(int x, int y)
{
	Position.x = x;
	Position.y = y;
	initialPosition.x = x;
	initialPosition.y = y;
}

bool Enemy::Damage(int n)
{
	lifes -= n;
	if (lifes <= 0)
		return true;
	return false;
}

bool Enemy::Damage() { return Damage(1); }

int Enemy::GetLifes() { return lifes; }

void Enemy::SetDistanceToCamera(int frontal, int lateral)
{
	distanceToCamera->Set(frontal, lateral);

	// Position transition

	int index = (frontal - 1) * 3 + (lateral - 1);
	Vector2 nextPosition = Vector2(positions[index]->x, positions[index]->y);

	if (currentPosition->x != -1)
		oldPosition->Set(currentPosition->x, currentPosition->y);
	else
		oldPosition->Set(nextPosition.x, nextPosition.y);
	currentPosition->Set(nextPosition.x, nextPosition.y);

	diffPosition->Set(currentPosition->x - oldPosition->x, currentPosition->y - oldPosition->y);

	// Size transition

	if (currentSize->y != -1)
		oldSize->Set(currentSize->x, currentSize->y);
	else
		oldSize->Set(sizes[frontal-1]->x, sizes[frontal-1]->y);

	currentSize->Set(sizes[frontal-1]->x, sizes[frontal-1]->y);
	diffSize->Set(currentSize->x - oldSize->x, currentSize->y - oldSize->y);
}

void Enemy::UpdateSprite()
{
	Vector2F Position = Vector2F
		( oldPosition->x + timer.GetPercentageFull()*diffPosition->x,
		  oldPosition->y + timer.GetPercentageFull()*diffPosition->y);

	Vector2F Size = Vector2F
		( oldSize->x + timer.GetPercentageFull()*diffSize->x,
		  oldSize->y + timer.GetPercentageFull()*diffSize->y);

	sprite->SetPosition(Position.x, Position.y);
	sprite->SetSize(Size.x, Size.y);
}

void Enemy::SetVisible(bool isVisible)
{
	if (!isVisible)
	{
		sprite->SetPosition(200, 200);
		currentPosition->Set(-1, -1);
		currentSize->Set(-1, -1);
		visible = false;
	}
	else
	{
		visible = true;
	}
}

bool Enemy::IsVisible() { return visible; }

void Enemy::SetScreenPositions(int id)
{
	switch (id)
	{
	case 1:

		// Si distancia frontal es 1:
		positions[0]->Set(-55 + 20 * channel, -1); // Si está a la izquierda
		positions[1]->Set(7 + 20 * channel, -1); // Si está al centro
		positions[2]->Set(75 + 20 * channel, -1); // Si está a la derecha
		// Si distancia frontal es 2:
		positions[3]->Set(-25 + 13 * channel, 21.7); // Si está a la izquierda
		positions[4]->Set(20 + 13 * channel, 21.7); // Si está al centro
		positions[5]->Set(65 + 13 * channel, 21.7); // Si está a la derecha
		// Si distancia frontal es 3:
		positions[6]->Set(-5 + 9.1 * channel, 33); // Si está a la izquierda
		positions[7]->Set(30 + 9.1 * channel, 33); // Si está al centro
		positions[8]->Set(65 + 9.1 * channel, 33); // Si está a la derecha
		// Si distancia frontal es 4:
		positions[9]->Set(5 + 7.5 * channel, 38.5); // Si está a la izquierda
		positions[10]->Set(35 + 7.5 * channel, 38.5); // Si está al centro
		positions[11]->Set(65 + 7.5 * channel, 38.5); // Si está a la derecha

		// TAMAÑOS
		sizes[0]->Set(27, 33.75);
		sizes[1]->Set(18, 22.5);
		sizes[2]->Set(12, 15);
		sizes[3]->Set(8, 10);

		break;

	}
}

void Enemy::SetChannel(int cnnel)
{
	channel = cnnel;
	SetScreenPositions(ID);
}

void Enemy::InitVectors()
{
	oldPosition = new Vector2F(-1, -1);
	currentPosition = new Vector2F(-1, -1);
	oldSize = new Vector2F(-1, -1);
	currentSize = new Vector2F(-1, -1);
	diffPosition = new Vector2F(-1, -1);
	diffSize = new Vector2F(-1, -1);

	distanceToCamera = new Vector2();

	for (int i = 0; i < 12; ++i)
		positions[i] = new Vector2F();
	for (int i = 0; i < 4;++i)
		sizes[i] = new Vector2F();
}

string Enemy::GetAnimationInfo()
{
	string info = "From (" + std::to_string(oldPosition->x) + ", " + std::to_string(oldPosition->y) + ") to (" + std::to_string(currentPosition->x) + ", " + std::to_string(currentPosition->y) + ")";
	info += "\n we're at (" + std::to_string(sprite->GetPosition().x) + ", " + std::to_string(sprite->GetPosition().y);

	return info;
}

Vector2 Enemy::DistanceToCamera() { return Vector2(distanceToCamera->x, distanceToCamera->y); }