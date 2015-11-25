#include "Enemy.h"
#include "Laberynth.h"
#include <time.h>
#include <cstdlib>

USING_NS_CC;

Enemy::Enemy(void)
{

}

Enemy::Enemy(int x, int y, int rango, float duracion)
{
		Position.x = x;
		Position.y = y;
		range = rango;
		duration = duracion;
		canForward = true;
		canBackward = false;
		canLeft = false;
		canRight = false;
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

void Enemy::whereIgo()
{
		int numeroAleatorio;
		if(canForward == true && canRight == true && canLeft == true){
			 srand (time(NULL));
			 numeroAleatorio = rand() % 3;
			 if(numeroAleatorio == 2) stepForward();
				else if(numeroAleatorio == 1) turnRight();
				else turnLeft();
		}
		else if(canForward == true && canRight == true){
			srand (time(NULL));
			numeroAleatorio = rand() % 2;
			if(numeroAleatorio == 1) stepForward();
			else turnRight();
		}
		else if(canForward == true && canLeft == true){
			srand (time(NULL));
			numeroAleatorio = rand() % 2;
			if(numeroAleatorio == 1) stepForward();
			else turnLeft();
		}
		else if(canForward == true){
			stepForward();
		}
		else stepBackward();

}

