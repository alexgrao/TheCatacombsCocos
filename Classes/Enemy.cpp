#include "Enemy.h"
#include "Laberynth.h"
#include "cocos2d.h"
#include "Assets.h"
#include <time.h>
#include <cstdlib>

USING_NS_CC;

Enemy::Enemy(void)
{

}

Enemy::Enemy(int x, int y, int vidas, int rango, float duracion)
{
	Position.x = x;
	Position.y = y;
	lifes = vidas;
	range = rango;
	timer = CatacombTimer(duracion);
}

Enemy::Enemy(int id)
{
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
	timer += delta;
	if (timer >= duration)
	{
		timer = timer - duration;
		return true;
	}
	return false;
}

void Enemy::Load(int id)
{
	switch (id)
	{
	case 1:
		timer = CatacombTimer(1);
		lifes = 3;
		imageSprite = Assets::Rat;
		range = 1;
		channel = 0;
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

double Enemy::GetTime() { return timer; }

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