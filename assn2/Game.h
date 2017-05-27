#ifndef __GAME_H__
#define __GAME_H__

#include "Map.h"
#include "Player.h"

class GAME{
public:
	MAP map;
	PLAYER player;	//object of character
	GLint pro;
	GLint model;
	float camera;

	void init();
	void draw();
	bool finished();	//충돌 판정
	bool treehere();
	void move();
};

#endif