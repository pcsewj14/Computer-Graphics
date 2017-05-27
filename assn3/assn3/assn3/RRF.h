#ifndef __RRF_H__
#define __RRF_H__

#include "CLT.h"

class ROAD {
public:
	vec3 rigidroad[6];
	vec4 rigidcolor[6];
	vec3 road[MAP_SIZE];
	CAR car;
	GLuint vPosition[MAP_SIZE];
	GLuint vColor[MAP_SIZE];
	GLuint roadB;

	void load();
	void init(int* map, GLuint program);
	void draw(GLint pro, GLint model);
	void move();
};

class RIVER {
public:
	vec3 river[6];
	vec4 river_color[6];
	LOG log;
	GLuint vPosition;
	GLuint vColor;
	GLuint riverB;

	void init(int num, GLuint program, float di);
	void buffer();
	void draw(GLint pro, GLint model);
	void move();
};

class FIELD {
public:
	vec3 rigidfield[6];
	vec4 rigidcolor[6];
	vec3 field[MAP_SIZE];
	TREE tree;
	GLuint vPosition[MAP_SIZE];
	GLuint vColor[MAP_SIZE];
	GLuint fieldB;

	void load();
	void init(int* map, GLuint program);
	void draw(GLint pro, GLint model);
};

#endif