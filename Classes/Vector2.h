#ifndef __VECTOR2_H__
#define __VECTOR2_H__

#include "cocos2d.h"

class Vector2
{
public:
	//Variables
	int x, y;

	//Funciones
	Vector2();
	Vector2(int, int);
	Vector2 Copy();
	void Set(int, int);
};

#endif