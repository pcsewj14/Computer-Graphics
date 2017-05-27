#include "Game.h"

int mode;

void GAME::load()
{
	map.load();
}

void GAME::init()
{
	camera = 0; mode = 1;
	direc = 0;

	glewExperimental = GL_TRUE;
	glewInit();

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint program = InitShader("vshader.glsl", "fshader.glsl");
	glUseProgram(program);
	pro = glGetUniformLocation(program, "projection");
	model = glGetUniformLocation(program, "model_view");

	map.init(program);
	player.init(program);	//character init
	
	map.buffer();
	player.buffer();	//character buffer

	glClearColor(0.2, 0.8, 1.0, 0.0);
}

void GAME::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	mat4 m;
	if (mode == 1)
		m = Ortho2D(-1.0 + camera, 1.0 + camera, -1.0, 1.0);
	else if (mode == 2)//시점의 mode (1, 2, 3으로 바꿀 수 있음)
	{
		if (direc == 0)//방향키에 따른 방향
		{
			vec4 eye = vec4(player.pos_x - 0.8, player.pos_y - 1, 1.25, 0.0);
			vec4 at = vec4(player.pos_x + 10, player.pos_y - 1, 0.0, 0.0);
			vec4 up = vec4(0.0, 0.0, 1.0, 0.0);//z축 방향으로 서있음
			m = Perspective(20, 1, 0.01, 5.0)*LookAt(eye, at, up);	//eye - at 방향으로 perspective가 일어남
																	//y방향으로 20도 만큼 본다. x방향으로 20도의 1배만큼 본다. 0.01 front clipping. 5.0 back clipping
		}
		else if (direc == 1)
		{
			vec4 eye = vec4(player.pos_x - 1.0, player.pos_y + 0.8, 1.25, 0.0);
			vec4 at = vec4(player.pos_x - 1.0, player.pos_y - 10, 0.0, 0.0);
			vec4 up = vec4(0.0, 0.0, 1.0, 0.0);
			m = Perspective(20, 1, 0.01, 5.0)*LookAt(eye, at, up);
		}
		else
		{
			vec4 eye = vec4(player.pos_x + 1.0, player.pos_y - 0.8, 1.25, 0.0);
			vec4 at = vec4(player.pos_x + 1.0, player.pos_y + 10, 0.0, 0.0);
			vec4 up = vec4(0.0, 0.0, 1.0, 0.0);
			m = Perspective(20, 1, 0.01, 5.0)*LookAt(eye, at, up);
		}
	}
	else if (mode == 3)
	{
		if (direc == 0)//방향키에 따른 방향
		{
			vec4 eye = vec4(player.pos_x + 0.3, player.pos_y - 1, 1.1, 0.0);	//-1을 안해주면 matrix ㅜ을 적용안한 상태로 나오는거같아서 1을 빼줬는데
			vec4 at = vec4(player.pos_x + 10, player.pos_y - 1, -1.7, 0.0);					//문제는 얘가 어디를 보고있는건지도 잘 모르겠어...
			vec4 up = vec4(0.0, 0.0, 1.0, 0.0);//z축 방향으로 서있음
			m = Perspective(90, 1, 0.01, 5.0)*LookAt(eye, at, up);	//eye - at 방향으로 perspective가 일어남
																	//y방향으로 20도 만큼 본다. x방향으로 20도의 1배만큼 본다. 0.01 front clipping. 5.0 back clipping
		}
		else if (direc == 1)
		{
			vec4 eye = vec4(player.pos_x - 1.0, player.pos_y - 0.3, 1.1, 0.0);
			vec4 at = vec4(player.pos_x - 1.0, player.pos_y - 10, -1.7, 0.0);
			vec4 up = vec4(0.0, 0.0, 1.0, 0.0);
			m = Perspective(90, 1, 0.01, 5.0)*LookAt(eye, at, up);
		}
		else
		{
			vec4 eye = vec4(player.pos_x + 1.0, player.pos_y + 0.3, 1.1, 0.0);
			vec4 at = vec4(player.pos_x + 1.0, player.pos_y + 10, -1.7, 0.0);
			vec4 up = vec4(0.0, 0.0, 1.0, 0.0);
			m = Perspective(90, 1, 0.01, 5.0)*LookAt(eye, at, up);
		}
		/*(if (direc == 0)
		{
			vec4 eye = vec4(-1+player.pos_x - 1, -1+player.pos_y, 1.7, 0.0);
			vec4 at = vec4(20, -1+player.pos_y, -0.5, 0.0);
			vec4 up = vec4(0.0, 0.0, 1.0, 0.0);
			m = Perspective(20, 1, 0.01, 4.0)*LookAt(eye, at, up);
		}
		else if (direc == 1)
		{
			vec4 eye = vec4(-1+player.pos_x, -1+player.pos_y + 0.5, 1.7, 0.0);
			vec4 at = vec4(-1+player.pos_x, -20, 0.5, 0.0);
			vec4 up = vec4(0.0, 0.0, 1.0, 0.0);
			m = Perspective(20, 1, 0.01, 1.0)*LookAt(eye, at, up);
		}
		else
		{
			vec4 eye = vec4(-1+player.pos_x, -1+player.pos_y - 0.5, 1.7, 0.0);
			vec4 at = vec4(-1+player.pos_x, 20, 0.5, 0.0);
			vec4 up = vec4(0.0, 0.0, 1.0, 0.0);
			m = Perspective(20, 1, 0.01, 5.0)*LookAt(eye, at, up);
		}*/
	}
	mat4 n = Translate(-1.0, -1.0, 0.0);
	glUniformMatrix4fv(pro, 1, GL_TRUE, m);
	glUniformMatrix4fv(model, 1, GL_TRUE, n);

	map.draw(pro, model);
	player.draw(pro, model);	//character draw

	glutSwapBuffers();
}

//충돌검사
bool GAME::finished()
{
	if (player.theta[RightUpperArm] != 180)
		return false;

	int i = (int)((player.pos_x + 0.9) * 10 + 0.5) / 2;
	float playery = player.pos_y + 1;
	float playerw = TORSO_WIDTH * 0.5 + UPPER_ARM_WIDTH;
	
	if (i >= MAP_SIZE) return true;
	
	
	for (int j = 0; j < CAR_N; j++)
	{
		float cary = map.road.car.car[i][j].y + map.road.car.cmove[i][j] - 0.2;
		float cwidth = map.road.car.width;

		if ((cary < playery + playerw) && (playery - playerw < cary + cwidth) && cary != 0)
			return true;
	}

	if (-camera > player.pos_x + 1.1)
		return true;

	if (playery >= 2.08 || playery <= -0.12)
		return true;

	for (int j = 0; j < LOG_N; j++)
	{
		float logy = map.river[i].log.log[j][0].y + map.river[i].log.lmove[j];
		float lwidth = map.river[i].log.width;

		if ((logy - 0.01 < playery - 0.08) && (playery + 0.12 < logy + lwidth + 0.01))
			return false;
	}
	if (map.map[i] == _river)
		return true;

	return false;
}

bool GAME::treehere()
{
	int i = (int)((player.pos_x + 0.9) * 10 + 0.5) / 2;
	int j = (int)((player.pos_y + 1) / 0.222 + 0.5);

	if (map.field.tree.tree[i][j].x == 0)
		return false;
	else
		return true;
}

void GAME::move()
{
	camera = player.pos_x + 0.9;

	map.move();
	if (finished()) exit(0);

	int i = (int)((player.pos_x + 0.9) * 10 + 0.5) / 2;
	/*if (map.map[i] == _river)
	{
		player.pos_y += map.river[i].log.speed*map.river[i].log.direc;
		player.nodes[Torso].transform = Translate(player.pos_x, player.pos_y, 0.0) * RotateX(-90);
	}*/
	glutPostRedisplay();
}

void GAME::keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case '1':
		mode = 1;
		//mat4 Perspective(const GLfloat fovy, const GLfloat aspect,
		//	const GLfloat zNear, const GLfloat zFar)
		break;
	case '2':
		mode = 2;
		//vec4 eye = vec4(game.player.pos_x - 0.2, game.player.pos_y, 0.0, 0.0);
		break;
	case '3':
		mode = 3;
		break;
	}
	glutPostRedisplay();
}