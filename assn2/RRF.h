#ifndef __RRF_H__
#define __RRF_H__

#include "CLT.h"

class ROAD {
public:
	vec3 road[6];
	vec4 road_color[6];
	CAR car;
	GLuint vPosition;
	GLuint vColor;
	GLuint roadB;

	void init(int num, GLuint program);
	void buffer();
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
	vec3 field[6];
	vec4 field_color[6];
	TREE tree;
	GLuint vPosition;
	GLuint vColor;
	GLuint fieldB;

	void init(int num, GLuint program);
	void buffer();
	void draw(GLint pro, GLint model);
};

#endif