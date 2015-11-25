#ifndef __ENEMY_H__
#define __ENEMY_H__

using namespace std;

#include "cocos2d.h"
#include "Vector2.h"
#include "Laberynth.h"
#include "CatacombTimer.h"

USING_NS_CC;

class Enemy
{
private:
	CatacombTimer timer;
	int lifes; // vida antes de morirse.
	int range; //Rango de movimiento
	const char* imageSprite; // Imagen del enemigo
	Vector2 initialPosition; // posicion inicial

public:
	// variables
	Vector2 Position; // Punto posición
	Vector2 Direction; // Vector Direccion
	Vector2 Left; //Vector izquierdo

	int channel;

	// funciones
	Enemy(); //Constructor 1
	Enemy(int, int, int, int, float); //Constructor 2
	Enemy(int);
	void turnLeft(); //Giro a la izquierda
	void turnRight(); //Giro a la derecha
	void stepForward(); //Paso delante
	void stepBackward(); //Paso atras
	void whereIgo(Laberynth*); //Donde va a ir el enemigo
	bool CheckTimer(float delta);

	void Load(int);
	const char* GetSprite();
	void SearchInitialDirection(Laberynth*);

	double GetTime();

	Vector2 GetInitialPosition();
	void SetPosition(int, int);

	bool Damage();
	bool Damage(int);
	int GetLifes();

};

#endif