#ifndef __LABERYNTH_H__
#define __LABERYNTH_H__

#include "cocos2d.h"
#include "Vector2.h"

class Laberynth
{
private:
	//Variables
	int** labMatrix;
	Vector2 entrance;
	Vector2 exit;
	Vector2 size;

	//Funciones
	void findFields();
public:
	//Variables


	//Funciones
	int field(int, int);
	bool isWall(int, int);
	bool isWall(Vector2);
	bool isIn(int, int);
	void Load(int, int);
	Vector2* GetEntrance();
	Vector2* GetExit();
	Vector2* Size();
};

#endif