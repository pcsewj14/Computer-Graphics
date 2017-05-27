#pragma once

#ifndef BUILDING_H
#define BUILDING_H

#include <iostream>
#include <fstream>
#include <vector>
#include "Angel.h"
#include "Texture.h"
#include "lodepng.h"

using namespace std;

vector<string> tokenize(string str, string delim);

class B0{
public:
	vec3 vertex[20][3];
	vec4 color[20][3];
	vec2 texture[20][3];

	int fcount;
	
	vec3 b0[2];

	GLuint vPosition;
	GLuint vColor;
	GLuint vTexture;
	GLuint buffer;

	Texture tex;
	mat4 rest;

	void load();
	void init(GLuint program);
	void draw(GLint pro, GLint model);
};

class B1 {
public:
	vec3 vertex[136][3];
	vec4 color[136][3];
	vec2 texture[136][3];

	int fcount;

	vec3 b1;

	GLuint vPosition;
	GLuint vColor;
	GLuint vTexture;
	GLuint buffer;

	Texture tex;
	mat4 rest;

	void load();
	void init(GLuint program);
	void draw(GLint pro, GLint model);
};

class B2 {
public:
	vec3 vertex[44][3];
	vec4 color[44][3];
	vec2 texture[44][3];

	int fcount;

	vec3 b2;

	GLuint vPosition;
	GLuint vColor;
	GLuint vTexture;
	GLuint buffer;

	Texture tex;
	mat4 rest;

	void load();
	void init(GLuint program);
	void draw(GLint pro, GLint model);
};

class B3 {
public:
	vec3 vertex[48][3];
	vec4 color[48][3];
	vec2 texture[48][3];

	int fcount;

	vec3 b3;

	GLuint vPosition;
	GLuint vColor;
	GLuint vTexture;
	GLuint buffer;

	Texture tex;
	mat4 rest;

	void load();
	void init(GLuint program);
	void draw(GLint pro, GLint model);
};

class APT {
public:
	vec3 vertex[12][3];
	vec4 color[12][3];
	vec2 texture[12][3];

	int fcount;

	vec3 apt[4];

	GLuint vPosition;
	GLuint vColor;
	GLuint vTexture;
	GLuint buffer;

	Texture tex;
	mat4 rest;

	void load();
	void init(GLuint program);
	void draw(GLint pro, GLint model);
};

#endif