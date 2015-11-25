#ifndef __ENEMY_SCENE_H__
#define __ENEMY_SCENE_H__

using namespace std;

#include "cocos2d.h"
#include "Vector2.h"

class Enemy
{
public:
	// variables
	Vector2 Position; // Punto posición
	Vector2 Direction; // Vector Direccion
	Vector2 Left; //Vector izquierdo
	int range; //Rango de movimiento
	double duration; //Tiempo que pasa entre paso y paso del enemigo
	bool canForward;
	bool canBackward;
	bool canLeft;
	bool canRight;

	// funciones
	Enemy(); //Constructor 1
	Enemy(int, int, int, float); //Constructor 2
	void turnLeft(); //Giro a la izquierda
	void turnRight(); //Giro a la derecha
	void stepForward(); //Paso delante
	void stepBackward(); //Paso atras
	void whereIgo(); //Donde va a ir el enemigo

};

#endif