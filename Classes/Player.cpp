#include "Player.h"

USING_NS_CC;

Player::Player(void)
{

}

Player::Player(int x, int y)
{
	Position.x = x;
	Position.y = y;
}

void Player::turnLeft()
{
	int x = -Direction.x;
	int y = -Direction.y;
	Direction.x = Left.x;
	Direction.y = Left.y;
	Left.x = x;
	Left.y = y;
}

void Player::turnRight()
{
	int x = -Left.x;
	int y = -Left.y;
	Left.x = Direction.x;
	Left.y = Direction.y;
	Direction.x = x;
	Direction.y = y;
}

void Player::stepForward()
{
	if (canForward)
	{
		Position.x += Direction.x;
		Position.y += Direction.y;
	}
}

void Player::stepBackward()
{
	if (canBackward)
	{
		Position.x -= Direction.x;
		Position.y -= Direction.y;
	}
}

float Player::GetBattery()
{
	return battery;
}

void Player::RefillBattery() { battery = 100; }

void Player::AddBattery(float quantity)
{
	battery += quantity;
	if (battery > 100) battery = 100;
	else if (battery < 0) battery = 0;
}

void Player::AddBullets(int tipo, int quantity)
{
	bullets[tipo] += quantity;
}

void Player::AddBengalas(int color, int quantity)
{
	bengalas[color] += quantity;
}

int Player::BulletsCount(int tipo) { return bullets[tipo]; }

int Player::BengalasCount(int color) { return bengalas[color]; }

<<<<<<< HEAD
// Timer for animation

=======
void Player::GenerarObjetos(Player* p) {
	//RefillBattery();
	p->AddBattery(25);
	srand(time(NULL));
	for (int i = 0; i < 4; i++) {
		probabilidadBengalas = rand() % 2 + 1; // numero entre 1 y 2;
		probabilidadBalas = rand() % 2 + 1; // numero entre 1 y 2;
		if (probabilidadBengalas == 1) p->AddBengalas(i, 1);
		if (probabilidadBalas == 1) p->AddBullets(i, 1);
	}

}
>>>>>>> origin/master
