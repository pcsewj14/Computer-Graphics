#include "Player.h"

typedef Angel::vec4 point4;
typedef Angel::vec4 color4;

const int NumVertices = 36; //(6 faces)(2 triangles/face)(3 vertices/triangle)

point4 points[10][NumVertices];
color4 colors[10][NumVertices];

point4 vertices[8] = {
	point4(-0.5, -0.5, 0.5, 1.0),
	point4(-0.5, 0.5, 0.5, 1.0),
	point4(0.5, 0.5, 0.5, 1.0),
	point4(0.5, -0.5, 0.5, 1.0),
	point4(-0.5, -0.5, -0.5, 1.0),
	point4(-0.5, 0.5, -0.5, 1.0),
	point4(0.5, 0.5, -0.5, 1.0),
	point4(0.5, -0.5, -0.5, 1.0)
};

// RGBA olors
color4 vertex_colors[NumNodes] = {
	color4(1.0, 1.0, 1.0, 1.0),  //white
	color4(1.0, 0.9, 0.6, 1.0),  //살색?
	color4(1.0, 0.0, 0.0, 1.0),  // red
	color4(1.0, 0.9, 0.6, 1.0),  //살색?
	color4(1.0, 0.0, 0.0, 1.0),  // red
	color4(1.0, 0.9, 0.6, 1.0),  //살색?
	color4(0.0, 0.0, 1.0, 1.0),  // blue
	color4(1.0, 0.9, 0.6, 1.0),  //살색?
	color4(0.0, 0.0, 1.0, 1.0),  // blue
	color4(1.0, 0.9, 0.6, 1.0),  //살색?
};

class MatrixStack {
	int    _index;
	int    _size;
	mat4*  _matrices;

public:
	MatrixStack(int numMatrices = 32) :_index(0), _size(numMatrices)
	{
		_matrices = new mat4[numMatrices];
	}

	~MatrixStack()
	{
		delete[]_matrices;
	}

	void push(const mat4& m) {
		assert(_index + 1 < _size);
		_matrices[_index++] = m;
	}

	mat4& pop(void) {
		assert(_index - 1 >= 0);
		_index--;
		return _matrices[_index];
	}
};

MatrixStack  mvstack;
mat4         model_view;

GLint ModelView;
GLint Projection;
GLuint playB[NumNodes];
GLuint vPosition[NumNodes];
GLuint vColor[NumNodes];
int index;

void PLAYER::init(GLuint program)
{
	for (int i = 0; i < NumNodes; i++)
	{
		index = 0;
		colorcube(i);
	}

	// Initialize tree
	pos_x = -0.9;
	pos_y = 0.03;
	pos_z = UPPER_LEG_HEIGHT + LOWER_LEG_HEIGHT;
	initNodes();

	for (int i = 0; i < NumNodes; i++)
	{
		vPosition[i] = glGetAttribLocation(program, "vPosition");
		glEnableVertexAttribArray(vPosition[i]);

		vColor[i] = glGetAttribLocation(program, "vColor");
		glEnableVertexAttribArray(vColor[i]);
	}

	ModelView = glGetUniformLocation(program, "model_view");
	Projection = glGetUniformLocation(program, "projection");

	glEnable(GL_DEPTH_TEST);
}

void PLAYER::buffer()
{
	for (int i = 0; i < NumNodes; i++)
	{
		glGenBuffers(1, &playB[i]);
		glBindBuffer(GL_ARRAY_BUFFER, playB[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(points[i]) + sizeof(colors[i]),
			NULL, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points[i]), points[i]);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(points[i]), sizeof(colors[i]), colors[i]);
	}
}

void PLAYER::reshape(int width, int height)
{
	glViewport(0, 0, width, height);

	GLfloat left = -10.0, right = 10.0;
	GLfloat bottom = -10.0, top = 10.0;
	GLfloat zNear = -10.0, zFar = 10.0;

	GLfloat aspect = GLfloat(width) / height;

	if (aspect > 1.0) {
		left *= aspect;
		right *= aspect;
	}
	else {
		bottom /= aspect;
		top /= aspect;
	}

	mat4 projection = Ortho(left, right, bottom, top, zNear, zFar);
	glUniformMatrix4fv(Projection, 1, GL_TRUE, projection);

	model_view = mat4(1.0);   // An Identity matrix
}

void PLAYER::quad(int idx, int a, int b, int c, int d)
{
	colors[idx][index] = vertex_colors[idx]; points[idx][index] = vertices[a]; index++;
	colors[idx][index] = vertex_colors[idx]; points[idx][index] = vertices[b]; index++;
	colors[idx][index] = vertex_colors[idx]; points[idx][index] = vertices[c]; index++;
	colors[idx][index] = vertex_colors[idx]; points[idx][index] = vertices[a]; index++;
	colors[idx][index] = vertex_colors[idx]; points[idx][index] = vertices[c]; index++;
	colors[idx][index] = vertex_colors[idx]; points[idx][index] = vertices[d]; index++;
}

void PLAYER::colorcube(int index)
{
	quad(index, 1, 0, 3, 2);
	quad(index, 2, 3, 7, 6);
	quad(index, 3, 0, 4, 7);
	quad(index, 6, 5, 1, 2);
	quad(index, 4, 5, 6, 7);
	quad(index, 5, 4, 0, 1);
}

void PLAYER::traverse(Node* node)
{
	if (node == NULL) { return; }

	mvstack.push(model_view);

	model_view *= node->transform;
	node->render();

	if (node->child) { traverse(node->child); }

	model_view = mvstack.pop();

	if (node->sibling) { traverse(node->sibling); }
}

void torso()
{
	mvstack.push(model_view);

	mat4 instance = (Translate(0.0, 0.5 * TORSO_HEIGHT, 0.0) *
		Scale(TORSO_WIDTH, TORSO_HEIGHT, TORSO_WIDTH));
	
	glBindBuffer(GL_ARRAY_BUFFER, playB[Torso]);
	glVertexAttribPointer(vPosition[Torso], 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));
	glVertexAttribPointer(vColor[Torso], 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sizeof(points[Torso])));

	glUniformMatrix4fv(ModelView, 1, GL_TRUE, model_view * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

	model_view = mvstack.pop();
}

void head()
{
	mvstack.push(model_view);

	mat4 instance = (Translate(0.0, 0.5 * HEAD_HEIGHT, 0.0) *
		Scale(HEAD_WIDTH, HEAD_HEIGHT, HEAD_WIDTH));

	glBindBuffer(GL_ARRAY_BUFFER, playB[Head]);
	glVertexAttribPointer(vPosition[Head], 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));
	glVertexAttribPointer(vColor[Head], 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sizeof(points[Head])));

	glUniformMatrix4fv(ModelView, 1, GL_TRUE, model_view * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

	model_view = mvstack.pop();
}

void right_upper_arm()
{
	mvstack.push(model_view);

	mat4 instance = (Translate(0.0, 0.5 * UPPER_ARM_HEIGHT, 0.0) *
		Scale(UPPER_ARM_WIDTH,
			UPPER_ARM_HEIGHT,
			UPPER_ARM_WIDTH));

	glBindBuffer(GL_ARRAY_BUFFER, playB[RightUpperArm]);
	glVertexAttribPointer(vPosition[RightUpperArm], 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));
	glVertexAttribPointer(vColor[RightUpperArm], 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sizeof(points[RightUpperArm])));

	glUniformMatrix4fv(ModelView, 1, GL_TRUE, model_view * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

	model_view = mvstack.pop();
}

void right_lower_arm()
{
	mvstack.push(model_view);

	mat4 instance = (Translate(0.0, 0.5 * LOWER_ARM_HEIGHT, 0.0) *
		Scale(LOWER_ARM_WIDTH,
			LOWER_ARM_HEIGHT,
			LOWER_ARM_WIDTH));

	glBindBuffer(GL_ARRAY_BUFFER, playB[RightLowerArm]);
	glVertexAttribPointer(vPosition[RightLowerArm], 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));
	glVertexAttribPointer(vColor[RightLowerArm], 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sizeof(points[RightLowerArm])));

	glUniformMatrix4fv(ModelView, 1, GL_TRUE, model_view * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

	model_view = mvstack.pop();
}

void left_upper_arm()
{
	mvstack.push(model_view);

	mat4 instance = (Translate(0.0, 0.5 * UPPER_ARM_HEIGHT, 0.0) *
		Scale(UPPER_ARM_WIDTH,
			UPPER_ARM_HEIGHT,
			UPPER_ARM_WIDTH));

	glBindBuffer(GL_ARRAY_BUFFER, playB[LeftUpperArm]);
	glVertexAttribPointer(vPosition[LeftUpperArm], 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));
	glVertexAttribPointer(vColor[LeftUpperArm], 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sizeof(points[LeftUpperArm])));

	glUniformMatrix4fv(ModelView, 1, GL_TRUE, model_view * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

	model_view = mvstack.pop();
}

void left_lower_arm()
{
	mvstack.push(model_view);

	mat4 instance = (Translate(0.0, 0.5 * LOWER_ARM_HEIGHT, 0.0) *
		Scale(LOWER_ARM_WIDTH,
			LOWER_ARM_HEIGHT,
			LOWER_ARM_WIDTH));

	glBindBuffer(GL_ARRAY_BUFFER, playB[LeftLowerArm]);
	glVertexAttribPointer(vPosition[LeftLowerArm], 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));
	glVertexAttribPointer(vColor[LeftLowerArm], 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sizeof(points[LeftLowerArm])));

	glUniformMatrix4fv(ModelView, 1, GL_TRUE, model_view * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

	model_view = mvstack.pop();
}

void right_upper_leg()
{
	mvstack.push(model_view);

	mat4 instance = (Translate(0.0, 0.5 * UPPER_LEG_HEIGHT, 0.0) *
		Scale(UPPER_LEG_WIDTH,
			UPPER_LEG_HEIGHT,
			UPPER_LEG_WIDTH));

	glBindBuffer(GL_ARRAY_BUFFER, playB[RightUpperLeg]);
	glVertexAttribPointer(vPosition[RightUpperLeg], 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));
	glVertexAttribPointer(vColor[RightUpperLeg], 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sizeof(points[RightUpperLeg])));

	glUniformMatrix4fv(ModelView, 1, GL_TRUE, model_view * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

	model_view = mvstack.pop();
}

void right_lower_leg()
{
	mvstack.push(model_view);

	mat4 instance = (Translate(0.0, 0.5 * LOWER_LEG_HEIGHT, 0.0) *
		Scale(LOWER_LEG_WIDTH,
			LOWER_LEG_HEIGHT,
			LOWER_LEG_WIDTH));

	glBindBuffer(GL_ARRAY_BUFFER, playB[RightLowerLeg]);
	glVertexAttribPointer(vPosition[RightLowerLeg], 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));
	glVertexAttribPointer(vColor[RightLowerLeg], 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sizeof(points[RightLowerLeg])));

	glUniformMatrix4fv(ModelView, 1, GL_TRUE, model_view * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

	model_view = mvstack.pop();
}

void left_upper_leg()
{
	mvstack.push(model_view);

	mat4 instance = (Translate(0.0, 0.5 * UPPER_LEG_HEIGHT, 0.0) *
		Scale(UPPER_LEG_WIDTH,
			UPPER_LEG_HEIGHT,
			UPPER_LEG_WIDTH));

	glBindBuffer(GL_ARRAY_BUFFER, playB[LeftUpperLeg]);
	glVertexAttribPointer(vPosition[LeftUpperLeg], 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));
	glVertexAttribPointer(vColor[LeftUpperLeg], 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sizeof(points[LeftUpperLeg])));

	glUniformMatrix4fv(ModelView, 1, GL_TRUE, model_view * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

	model_view = mvstack.pop();
}

void left_lower_leg()
{
	mvstack.push(model_view);

	mat4 instance = (Translate(0.0, 0.5 * LOWER_LEG_HEIGHT, 0.0) *
		Scale(LOWER_LEG_WIDTH,
			LOWER_LEG_HEIGHT,
			LOWER_LEG_WIDTH));

	glBindBuffer(GL_ARRAY_BUFFER, playB[LeftLowerLeg]);
	glVertexAttribPointer(vPosition[LeftLowerLeg], 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));
	glVertexAttribPointer(vColor[LeftLowerLeg], 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sizeof(points[LeftLowerLeg])));

	glUniformMatrix4fv(ModelView, 1, GL_TRUE, model_view * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

	model_view = mvstack.pop();
}

void PLAYER::draw(GLint pro, GLint model)
{
	traverse(&nodes[Torso]);
}

void PLAYER::initNodes()
{
	mat4  m;

	m = Translate(pos_x, pos_y, pos_z) * RotateX(90) * RotateZ(theta[Torso]);
	nodes[Torso] = Node(m, torso, NULL, &nodes[Head]);

	m = Translate(0.0, TORSO_HEIGHT, 0.0);
	nodes[Head] = Node(m, head, &nodes[RightUpperArm], NULL);

	m = Translate(0.0, TORSO_HEIGHT, -0.5*(TORSO_WIDTH + UPPER_ARM_WIDTH)) *
		RotateZ(theta[RightUpperArm]);
	nodes[RightUpperArm] =
		Node(m, right_upper_arm, &nodes[LeftUpperArm], &nodes[RightLowerArm]);

	m = Translate(0.0, TORSO_HEIGHT, 0.5*(TORSO_WIDTH + UPPER_ARM_WIDTH)) *
		RotateZ(theta[LeftUpperArm]);
	nodes[LeftUpperArm] =
		Node(m, left_upper_arm, &nodes[RightUpperLeg], &nodes[LeftLowerArm]);

	m = Translate(0.0, 0.0, -0.5 * UPPER_LEG_WIDTH) *
		RotateZ(theta[RightUpperLeg]);
	nodes[RightUpperLeg] =
		Node(m, right_upper_leg, &nodes[LeftUpperLeg], &nodes[RightLowerLeg]);

	m = Translate(0.0, 0.0, 0.5 * UPPER_LEG_WIDTH) *
		RotateZ(theta[LeftUpperLeg]);
	nodes[LeftUpperLeg] =
		Node(m, left_upper_leg, NULL, &nodes[LeftLowerLeg]);

	m = Translate(0.0, UPPER_ARM_HEIGHT, 0.0) * RotateX(theta[RightLowerArm]);
	nodes[RightLowerArm] = Node(m, right_lower_arm, NULL, NULL);

	m = Translate(0.0, UPPER_ARM_HEIGHT, 0.0) * RotateX(theta[LeftLowerArm]);
	nodes[LeftLowerArm] = Node(m, left_lower_arm, NULL, NULL);

	m = Translate(0.0, UPPER_LEG_HEIGHT, 0.0) * RotateX(theta[RightLowerLeg]);
	nodes[RightLowerLeg] = Node(m, right_lower_leg, NULL, NULL);

	m = Translate(0.0, UPPER_LEG_HEIGHT, 0.0) * RotateX(theta[LeftLowerLeg]);
	nodes[LeftLowerLeg] = Node(m, left_lower_leg, NULL, NULL);
}