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
	int direc;
	float camera;

	void load();
	void init();
	void draw();
	bool finished();	//충돌 판정
	bool treehere();
	void move();
	void keyboard(unsigned char key, int x, int y);
};

#endif