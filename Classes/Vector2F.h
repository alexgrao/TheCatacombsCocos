#ifndef __VECTOR2F_H__
#define __VECTOR2F_H__

#include "cocos2d.h"

class Vector2F
{
public:
	//Variables
	float x, y;

	//Funciones
	Vector2F();
	Vector2F(float, float);
	Vector2F Copy();
	void Set(float, float);
};

#endif