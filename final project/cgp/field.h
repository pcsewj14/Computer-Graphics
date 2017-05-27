#pragma once

#ifndef FIELD_H
#define FIELD_H

#include "car.h"

class ROAD {
public:
	vec3 vertex[6];
	vec4 color[6];
	vec2 texture[6];

	vec3 lvertex[6];
	
	vec3 road;
	vec3 line;

	GLuint vPosition;
	GLuint vColor;
	GLuint vTexture;
	GLuint buffer[2];

	Texture tex;
	Texture ltex;
		
	void load();
	void init(GLuint program);
	void draw(GLint pro, GLint model);
};

class FIELD {
public:
	vec3 vertex[6];
	vec4 color[6];
	vec2 texture[6];

	vec3 field[2];

	GLuint vPosition;
	GLuint vColor;
	GLuint vTexture;
	GLuint buffer;

	Texture tex;

	void load();
	void init(GLuint program);
	void draw(GLint pro, GLint model);
};

class GRASS {
public:
	vec3 vertex[6];
	vec4 color[6];
	vec2 texture[6];

	vec3 grass[2];

	GLuint vPosition;
	GLuint vColor;
	GLuint vTexture;
	GLuint buffer;

	Texture tex;

	void load();
	void init(GLuint program);
	void draw(GLint pro, GLint model);
};

class TREE {
public:
	vec3 vertex[144][3];
	vec4 color[144][3];
	vec2 texture[144][3];

	int fcount;

	vec3 tree[2][20];

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

class BUILDING {
public:
	B0 b0;
	B1 b1;
	B2 b2;
	B3 b3;
	APT apt;

	void load();
	void init(GLuint program);
	void draw(GLint pro, GLint model);
};

class CAR {
public:
	BUS bus;
	SCAR car;
	RCAR rcar;
	TAXI taxi;

	void load();
	void init(GLuint program);
	void draw(GLint pro, GLint model);
	void move();
};

#endif