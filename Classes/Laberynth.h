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
	void setField(int, int, int);
	int field(int, int);
	bool isWall(int, int);
	bool isWall(Vector2);
	bool isExitEntrance(int, int);
	bool isExit(int, int);
	bool isEntrance(int, int);
	bool isIn(int, int);
	bool isEnemy(int, int);
	bool isMochila(int, int);
	void Load(int, int);
	int Get(int, int);
	void Set(int, int, int);
	Vector2* GetEntrance();
	Vector2* GetExit();
	Vector2* Size();
	void MoveEnemy(int, int, int, int);

};

#endif