#ifndef __PLAYER_SCENE_H__
#define __PLAYER_SCENE_H__

#include "cocos2d.h"
#include "Vector2.h"
#include "CatacombTimer.h"

class Player
{
private:
	CatacombTimer timer;

	// Objetos
	float battery; // porcentaje
	int bengalas[4] = { 0, 0, 0, 0 }; // rojas - azules - verdes - amarillas
	int bullets[4] = { 0, 0, 0, 0 };;    // tipo1 - tipo2 - tipo3 - tipo4
	float probabilidadBengalas;
	float probabilidadBalas;


public:
	// variables
	Vector2 Position;
	Vector2 Direction;
	Vector2 Left;
	bool canForward = true;
	bool canBackward = false;

	// funciones
	Player();
	Player(int, int);
	void turnLeft();
	void turnRight();
	void stepForward();
	void stepBackward();

	//Objetos
	void GenerarObjetos(Player *);
	float GetBattery();
	void RefillBattery();
	void AddBattery(float);
	void AddBullets(int, int);
	void AddBengalas(int, int);
	int BulletsCount(int);
	int BengalasCount(int);

};

#endif