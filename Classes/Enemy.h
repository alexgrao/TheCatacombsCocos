#ifndef __ENEMY_H__
#define __ENEMY_H__

using namespace std;

#include "cocos2d.h"
#include "Vector2.h"
#include "Vector2F.h"
#include "Laberynth.h"
#include "CatacombTimer.h"
#include "CentSprite.h"

USING_NS_CC;

class Enemy
{
private:
	CatacombTimer timer;
	int lifes; // vida antes de morirse.
	int range; //Rango de movimiento
	const char* imageSprite; // Imagen del enemigo
	Vector2 initialPosition; // posicion inicial
	int channel;

	// VARIABLES PARA ANIMACIÓN
	Vector2F* positions[4*3]; // Posiciones dependiendo de la distancia a la cámara
	Vector2F* sizes[4]; // Tamaños dependiendo de la distancia a la cámara
	Vector2F* oldPosition, *currentPosition, *diffPosition;
	Vector2F* oldSize, *currentSize, *diffSize;
	Vector2* distanceToCamera;

public:
	// variables
	int ID = 0;

	Vector2 Position; // Punto posición
	Vector2 Direction; // Vector Direccion
	Vector2 Left; //Vector izquierdo

	CentSprite* sprite;

	// funciones
	Enemy(); //Constructor 1
	Enemy(int, int, int, int, float); //Constructor 2
	Enemy(int);
	void turnLeft(); //Giro a la izquierda
	void turnRight(); //Giro a la derecha
	void stepForward(); //Paso delante
	void stepBackward(); //Paso atras
	void whereIgo(Laberynth*); //Donde va a ir el enemigo
	bool CheckTimer(float);
	void SetChannel(int);

	void Load(int);
	const char* GetSprite();
	void SearchInitialDirection(Laberynth*);

	double GetTime();

	Vector2 GetInitialPosition();
	void SetPosition(int, int);

	bool Damage();
	bool Damage(int);
	int GetLifes();

	// Funciones para animacion
	void SetDistanceToCamera(int, int);
	void UpdateSprite();
	void NotVisible();
	void SetScreenPositions(int);
	void InitVectors();
	Vector2 DistanceToCamera();
	string GetAnimationInfo();

};

#endif