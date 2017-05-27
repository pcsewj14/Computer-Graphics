#ifndef __RF_H__
#define __RF_H__

#include "CT.h"

class ROAD {
public:
	vec3 rigidroad[6];
	vec4 rigidcolor[6];
	vec3 road[MAP_SIZE];
	CAR car;
	GLuint vPosition[MAP_SIZE];
	GLuint vColor[MAP_SIZE];
	GLuint roadB;
	GLuint diffuse;
	Texture troad;
	vec2 texture[6];
	GLuint vtexture[MAP_SIZE];
	vec3 normal[6];
	GLuint vNormal[MAP_SIZE];

	void load();
	void init(int* map, GLuint program);
	void draw(int* map, GLint pro, GLint model);
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
	GLuint diffuse;
	Texture tfield;
	vec2 texture[6];
	GLuint vtexture[MAP_SIZE];
	vec3 normal[6];
	GLuint vNormal[MAP_SIZE];

	void load();
	void init(int* map, GLuint program);
	void draw(int* map, GLint pro, GLint model);
};

#endif