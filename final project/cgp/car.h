#pragma once

#ifndef CAR_H
#define CAR_H

#include "building.h"

class BUS {
public:
	vec3 vertex[876][3];
	vec4 color[876][3];
	vec2 texture[876][3];

	int fcount;
	
	float m[2];
	vec3 obj[2];

	GLuint vPosition;
	GLuint vColor;
	GLuint vTexture;
	GLuint buffer;

	Texture tex;
	mat4 rest[2];

	void load();
	void init(GLuint program);
	void draw(GLint pro, GLint model);
	void move();
};

class SCAR {
public:
	vec3 vertex[600][3];
	vec4 color[600][3];
	vec2 texture[600][3];

	int fcount;
	
	float m[2];
	vec3 obj[2];

	GLuint vPosition;
	GLuint vColor;
	GLuint vTexture;
	GLuint buffer;

	Texture tex;
	mat4 rest[2];

	void load();
	void init(GLuint program);
	void draw(GLint pro, GLint model);
	void move();
};

class RCAR {
public:
	vec3 vertex[600][3];
	vec4 color[600][3];
	vec2 texture[600][3];

	int fcount;

	float m[2];
	vec3 obj[2];

	GLuint vPosition;
	GLuint vColor;
	GLuint vTexture;
	GLuint buffer;

	Texture tex;
	mat4 rest[2];

	void load();
	void init(GLuint program);
	void draw(GLint pro, GLint model);
	void move();
};

class TAXI {
public:
	vec3 vertex[836][3];
	vec4 color[836][3];
	vec2 texture[836][3];

	int fcount;
	
	float m[2];
	vec3 obj[2];

	GLuint vPosition;
	GLuint vColor;
	GLuint vTexture;
	GLuint buffer;

	Texture tex;
	mat4 rest[2];

	void load();
	void init(GLuint program);
	void draw(GLint pro, GLint model);
	void move();
};

#endif