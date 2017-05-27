//#pragma once
#ifndef __CT_H__
#define __CT_H__

#include "Angel.h"
#include "texture.h"
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

#define CAR_N 5
#define MAP_SIZE 100

enum m { _field, _road};

vector<string> tokenize(string str, string delim);

class CAR {
public:
	vec3 rigidcar[79][8];
	vec4 rigidcolor[79][8];
	
	vec3 tvcar[158][3];
	vec3 wvcar[158][3];
	vec4 tcolor[158][3];
	vec2 ttex[158][3];
	vec2 wtex[158][3];
	vec3 ntex[158][3];
	vec3 tangent[158][3];
	vec3 bitangent[158][3];

	vec3 car[MAP_SIZE][CAR_N];
	GLuint vPosition[MAP_SIZE][CAR_N];
	GLuint vColor[MAP_SIZE][CAR_N];
	GLuint vtexture[MAP_SIZE][CAR_N];
	GLuint vNormal[MAP_SIZE][CAR_N];
	GLuint vtan[MAP_SIZE][CAR_N];
	GLuint vbitan[MAP_SIZE][CAR_N];

	GLuint carB[3];
	GLuint diffuse;
	GLuint normalmap;

	Texture wcar;
	Texture tcar;
	Texture no;
	mat4 rest;
	int mo;

	vec4 light_position;
	vec4 light_ambient;
	vec4 light_diffuse;
	vec4 light_specular;
	float shininess;

	float space[MAP_SIZE];
	float speed[MAP_SIZE];
	float direc[MAP_SIZE];
	float cmove[MAP_SIZE][CAR_N];
	float width;

	void load();
	void init(int* map, GLuint program);
	void draw(int* map, GLint pro, GLint model);
	void move();
	void reInit();
};

class TREE {
public:
	vec3 rigidtree[158][8];
	vec4 rigidcolor[158][8];

	vec3 tvtree[316][3];
	vec4 tcolor[316][3];
	vec2 ttex[316][3];
	vec3 wvtree[316][3];
	vec2 wtex[316][3];
	vec3 ntex[316][3];
	vec3 tangent[316][3];
	vec3 bitangent[316][3];

	vec3 tree[MAP_SIZE][10];
	GLuint vPosition;
	GLuint vColor;
	GLuint vtexture;
	GLuint vNormal;
	GLuint vtan;
	GLuint vbitan;

	GLuint treeB[3];
	GLuint diffuse;
	GLuint normalmap;

	Texture wtree;
	Texture ttree;
	Texture no;
	mat4 rest;
	int mo;

	vec4 light_position;
	vec4 light_ambient;
	vec4 light_diffuse;
	vec4 light_specular;
	float shininess;

	void load();
	void init(int* map, GLuint program);
	void draw(int* map, GLint pro, GLint model);
};

#endif