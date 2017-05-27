//#pragma once
#ifndef __CLT_H__
#define __CLT_H__

#include "Angel.h"
#include <ctime>
#include <cstdlib>

#define CAR_N 5
#define LOG_N 3

class CAR {
public:
	vec3 car[CAR_N][6];
	vec4 car_color[CAR_N][6];
	GLuint vPosition[CAR_N];
	GLuint vColor[CAR_N];
	GLuint carB[CAR_N];

	float space;
	float speed;
	float direc;
	float cmove[CAR_N];
	float width;

	void init(int i, GLuint program);
	void buffer();
	void draw(GLint pro, GLint model);
	void move();
	void reInit();
};

class LOG {
public:
	vec3 log[LOG_N][6];
	vec4 log_color[LOG_N][6];
	GLuint vPosition[LOG_N];
	GLuint vColor[LOG_N];
	GLuint logB[LOG_N];

	float space;
	float speed;
	float direc;
	float width;
	float lmove[LOG_N];

	void init(int i, GLuint program, float di);
	void buffer();
	void draw(GLint pro, GLint model);
	void move();
	void reInit();
};

class TREE {
public:
	vec3 tree[10][6];
	vec4 tree_color[10][6];
	GLuint vPosition;
	GLuint vColor;
	GLuint treeB;

	void init(int num, GLuint program);
	void buffer();
	void draw(GLint pro, GLint model);
};

#endif