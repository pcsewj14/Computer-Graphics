//#pragma once
#ifndef __CLT_H__
#define __CLT_H__

#include "Angel.h"
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

#define CAR_N 5
#define LOG_N 3
#define MAP_SIZE 100

enum m { _field, _road, _river };

vector<string> tokenize(string str, string delim);

class CAR {
public:
	vec3 rigidcar[79][8];
	vec4 rigidcolor[79][8];
	vec3 car[MAP_SIZE][CAR_N];
	GLuint vPosition[MAP_SIZE][CAR_N];
	GLuint vColor[MAP_SIZE][CAR_N];
	GLuint carB;
	mat4 rest;

	float space[MAP_SIZE];
	float speed[MAP_SIZE];
	float direc[MAP_SIZE];
	float cmove[MAP_SIZE][CAR_N];
	float width;

	void load();
	void init(int* map, GLuint program);
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
	vec3 rigidtree[158][8];
	vec4 rigidcolor[158][8];
	vec3 tree[MAP_SIZE][10];
	GLuint vPosition;
	GLuint vColor;
	GLuint treeB;
	mat4 rest;

	void load();
	void init(int* map, GLuint program);
	void draw(GLint pro, GLint model);
};

#endif