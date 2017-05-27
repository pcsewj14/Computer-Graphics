#ifndef __MAP_H__
#define __MAP_H__

#include "RRF.h"

#define MAP_SIZE 50

enum m { _field, _road, _river };

class MAP {
public:
	int map[MAP_SIZE];
	FIELD field[MAP_SIZE];
	ROAD road[MAP_SIZE];
	RIVER river[MAP_SIZE];
	vec3 rLine[MAP_SIZE * 10];
	vec4 rLine_color[MAP_SIZE * 10];
	float di[MAP_SIZE];
	GLuint vPosition;
	GLuint vColor;
	GLuint lineB;
	
	void init(GLuint program);
	void buffer();
	void draw(GLint pro, GLint model);
	void move();
};

#endif