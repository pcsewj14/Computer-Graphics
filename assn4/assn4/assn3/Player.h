#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Angel.h"
#include <assert.h>

#define TORSO_HEIGHT 0.06
#define TORSO_WIDTH 0.04
#define UPPER_ARM_HEIGHT 0.04
#define LOWER_ARM_HEIGHT 0.04
#define UPPER_LEG_WIDTH  0.02
#define LOWER_LEG_WIDTH  0.015
#define LOWER_LEG_HEIGHT 0.04
#define UPPER_LEG_HEIGHT 0.04
#define UPPER_ARM_WIDTH  0.02
#define LOWER_ARM_WIDTH  0.015
#define HEAD_HEIGHT 0.03
#define HEAD_WIDTH 0.03

enum {
	Torso, Head, RightUpperArm,	RightLowerArm, LeftUpperArm, LeftLowerArm,
	RightUpperLeg, RightLowerLeg, LeftUpperLeg,	LeftLowerLeg, NumNodes
};

struct Node {
	mat4  transform;
	void(*render)();
	Node* sibling;
	Node* child;

	Node() :
		render(NULL), sibling(NULL), child(NULL) {}

	Node(mat4& m, void(*render)(), Node* sibling, Node* child) :
		transform(m), render(render), sibling(sibling), child(child) {}
};

class PLAYER {
public:
	GLfloat	theta[NumNodes] = {
		0.0,    // Torso
		0.0,    // Head
		180.0,  // RightUpperArm
		0.0,    // RightLowerArm
		180.0,  // LeftUpperArm
		0.0,    // LeftLowerArm
		180.0,  // RightUpperLeg
		0.0,     // RightLowerLeg
		180.0,  // LeftUpperLeg
		0.0    // LeftLowerLeg
	};

	Node nodes[NumNodes];
	float width;
	float pos_x;
	float pos_y;
	float pos_z;

	void buffer();
	void reshape(int width, int height);
	void quad(int idx, int a, int b, int c, int d);
	void colorcube(int index);
	void traverse(Node* node);
	void draw(GLint pro, GLint model);
	void initNodes();
	void init(GLuint program);
};

#endif