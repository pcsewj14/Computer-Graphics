#include <iostream>
#include "field.h"
using namespace std;

GLint pro; GLint model; vec4 eye, at, up;
ROAD road; FIELD field; GRASS grass; TREE tree; BUILDING build; CAR car;
GLuint program; GLuint p2;
GLuint vao;
GLuint quadVao, quadVbo;
GLuint position, texCoords, moup, modo, time, mode;
GLuint framebuffer, texColorBuffer, rbo;
int ltime;
int mo;

GLfloat Positions[] = {
	-1.0f,  1.0f, -1.0f, -1.0f,	1.0f, -1.0f,
	-1.0f,  1.0f, 1.0f, -1.0f,	1.0f,  1.0f,
};

GLfloat TexCoords[] = {
	0.0f, 1.0f,	0.0f, 0.0f,	1.0f, 0.0f,
	0.0f, 1.0f,	1.0f, 0.0f,	1.0f, 1.0f
};


void load()
{
	road.load();
	field.load();
	grass.load();
	tree.load();
	build.load();
	car.load();
}

void init()
{
	mo = 0;

	glewExperimental = GL_TRUE;
	glewInit();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	program = InitShader("vshader.glsl", "fshader.glsl");
	p2 = InitShader("vfbo.glsl", "ffbo.glsl");

	pro = glGetUniformLocation(program, "projection");
	model = glGetUniformLocation(program, "model_view");

	glUniform1i(glGetUniformLocation(program, "texture"), 0);

	load();
	road.init(program);
	field.init(program);
	grass.init(program);
	tree.init(program);
	build.init(program);
	car.init(program);
	glBindVertexArray(0);

	eye = vec4(0, -0.8, 2, 0.0);
	at = vec4(0, 10, -0.5, 0.0);
	up = vec4(0.0, 0.0, 1.0, 0.0);

	glGenVertexArrays(1, &quadVao);
	glGenBuffers(1, &quadVbo);
	glBindVertexArray(quadVao);
	glBindBuffer(GL_ARRAY_BUFFER, quadVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Positions) + sizeof(TexCoords), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Positions), Positions);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(Positions), sizeof(TexCoords), TexCoords);

	position = glGetAttribLocation(p2, "position");
	glEnableVertexAttribArray(position);
	glVertexAttribPointer(position, 2, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));

	texCoords = glGetAttribLocation(p2, "texCoords");
	glEnableVertexAttribArray(texCoords);
	glVertexAttribPointer(texCoords, 2, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sizeof(Positions)));

	moup = glGetUniformLocation(p2, "upleft");
	modo = glGetUniformLocation(p2, "dright");
	time = glGetUniformLocation(p2, "time");
	mode = glGetUniformLocation(p2, "mode");
	GLuint para = glGetUniformLocation(p2, "shockParams");
	glUniform2f(moup, 0, 0);
	glUniform2f(modo, 700.0, 500.0);
	glUniform1f(time, 0.1);
	glUniform3f(para, 10.0, 0.8, 0.1);

	glBindVertexArray(0);

	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);

	glGenTextures(1, &texColorBuffer);
	glBindTexture(GL_TEXTURE_2D, texColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 700, 500, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 700, 500);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClearColor(0.2, 0.8, 1, 1);
	glEnable(GL_DEPTH_TEST);
}

void display()
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glUniform1f(time, 0.001*(glutGet(GLUT_ELAPSED_TIME) - ltime));
	cout << 0.001 * (glutGet(GLUT_ELAPSED_TIME) - ltime) << endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glActiveTexture(GL_TEXTURE0);
	glUseProgram(program);

	mat4 m = Perspective(90, 1, 0.01, 10.0)*LookAt(eye, at, up);
	mat4 n = Translate(-1, -1, 0);
	glUniformMatrix4fv(pro, 1, GL_TRUE, m);
	glUniformMatrix4fv(model, 1, GL_TRUE, n);

	glBindVertexArray(vao);
	road.draw(pro, model);
	field.draw(pro, model);
	grass.draw(pro, model);
	tree.draw(pro, model);
	build.draw(pro, model);
	car.draw(pro, model);

	glBindVertexArray(0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClearColor(0.2, 0.8, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	glUseProgram(p2);
	glBindVertexArray(quadVao);
	glBindTexture(GL_TEXTURE_2D, texColorBuffer);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	glutSwapBuffers();
}

void moveCar()
{
	car.move();

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'm':
		if (mo < 8)
		{
			mo++;
			glUniform1i(mode, mo);
		}
		else
		{
			mo = 0;
			glUniform1i(mode, mo);
		}
	}
	glutPostRedisplay();
}

void specialkeyboard(int key, int x, int y)
{
	vec4 e = (eye.x, eye.y, 0, 0);
	switch (key) {
	case GLUT_KEY_LEFT:
		at = RotateZ(20)*(at -e) + e;
		break;
	case GLUT_KEY_RIGHT:
		at = RotateZ(-20)*(at - e) + e;
		break;
	case GLUT_KEY_UP:
		vec4 ve = at - eye;
		eye += ve*vec4(0.01, 0.01, 0, 0);
		at += ve*vec4(0.01, 0.01, 0, 0);
		break;
	}
	mat4 m = Perspective(90, 1, 0.01, 5.0)*LookAt(eye, at, up);
	glUniformMatrix4fv(pro, 1, GL_TRUE, m);

	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		switch (button) {
		case GLUT_LEFT_BUTTON:
			glUniform2f(moup, x, y);
			ltime = glutGet(GLUT_ELAPSED_TIME);
			cout << x << " " << y << endl;
			break;	//마우스로 클릭한 부분만 필터가 적용되도록
		case GLUT_RIGHT_BUTTON:
			glUniform2f(moup, 0, 0);
			glUniform2f(modo, 700, 500);
		}
	}
	if (state == GLUT_UP)
	{
		switch (button) {
		case GLUT_LEFT_BUTTON:
			glUniform2f(modo, x, y);
			cout << x << " " << y << endl;
			break;
		}
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 500);

	glutInitContextVersion(3, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutCreateWindow("Computer Graphics");
	
	glewInit();
	init();

	glutDisplayFunc(display);
	glutIdleFunc(moveCar);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialkeyboard);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}