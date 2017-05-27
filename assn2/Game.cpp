#include "Game.h"

void GAME::init()
{
	camera = 0;

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

	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void GAME::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	mat4 i = Translate(0.0 + camera, 0.0, 0.0);
	mat4 n = Translate(-1.0, -1.0, 0.0);
	glUniformMatrix4fv(pro, 1, GL_TRUE, i);
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
	
	if (i >= MAP_SIZE) return true;
	
	for (int j = 0; j < CAR_N; j++)
	{
		
		float cary = map.road[i].car.car[j][0].y + map.road[i].car.cmove[j];
		float cwidth = map.road[i].car.width;

		if ((cary < playery + 0.12) && (playery - 0.08 < cary + cwidth) && cary != 0)
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
	int j = (int)((player.pos_y + 0.913) / 0.222 + 0.5);

	if (map.field[i].tree.tree[j][0].x == 0)
		return false;
	else
		return true;
}

void GAME::move()
{
	camera -= 0.00008;

	map.move();
	if (finished()) exit(0);

	int i = (int)((player.pos_x + 0.9) * 10 + 0.5) / 2;
	if (map.map[i] == _river)
	{
		player.pos_y += map.river[i].log.speed*map.river[i].log.direc;
		player.nodes[Torso].transform = Translate(player.pos_x, player.pos_y, 0.0);
	}
	

	glutPostRedisplay();
}