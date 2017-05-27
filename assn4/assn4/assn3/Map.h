#ifndef __MAP_H__
#define __MAP_H__

#include "RF.h"

class MAP {
public:
	int map[MAP_SIZE];
	FIELD field;

	ROAD road;
	vec3 line[6];
	vec4 color[6];
	vec3 normal[6];
	vec3 rLine[MAP_SIZE][5];
	vec2 texture[6];

	GLuint vPosition;
	GLuint vColor;
	GLuint vTexture;
	GLuint vNormal;
	GLuint diffuse;
	float shininess;

	GLuint lineB;
	Texture tline;
	
	void load();
	void init(GLuint program);
	void draw(GLint pro, GLint model);
	void move();
};

#endif