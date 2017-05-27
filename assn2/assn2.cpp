#include "Game.h"
#include <ctime>
#include <cstdlib>
#include <stdio.h>

GAME game;

void init()
{
	game.init();
}

void draw()
{
	game.draw();
}

void move()
{
	game.move();
}

void phase3(int value)
{
	game.player.theta[RightUpperArm] -= 20;
	game.player.nodes[RightUpperArm].transform = Translate(0.0, TORSO_HEIGHT, -0.5*(TORSO_WIDTH + UPPER_ARM_WIDTH)) *
		RotateZ(game.player.theta[RightUpperArm]);

	game.player.theta[LeftUpperArm] += 20;
	game.player.nodes[LeftUpperArm].transform = Translate(0.0, TORSO_HEIGHT, 0.5*(TORSO_WIDTH + UPPER_ARM_WIDTH)) *
		RotateZ(game.player.theta[LeftUpperArm]);

	game.player.theta[LeftUpperLeg] += 20;
	game.player.nodes[LeftUpperLeg].transform = Translate(0.0, 0.0, 0.25*(TORSO_WIDTH + UPPER_LEG_WIDTH)) *
		RotateZ(game.player.theta[LeftUpperLeg]);
	//glutTimerFunc(100, phase3, 1);
	glutPostRedisplay();
}

void phase2(int value)
{
	game.player.pos_x += 0.1;
	game.player.nodes[Torso].transform = Translate(game.player.pos_x, game.player.pos_y, 0.0);

	game.player.theta[RightUpperArm] -= 10;
	game.player.nodes[RightUpperArm].transform = Translate(0.0, TORSO_HEIGHT, -0.5*(TORSO_WIDTH + UPPER_ARM_WIDTH)) *
		RotateZ(game.player.theta[RightUpperArm]);

	game.player.theta[RightLowerArm] -= 20;
	game.player.nodes[RightLowerArm].transform = Translate(0.0, UPPER_ARM_HEIGHT, 0.0) * RotateZ(game.player.theta[RightLowerArm]);

	game.player.theta[LeftUpperArm] += 10;
	game.player.nodes[LeftUpperArm].transform = Translate(0.0, TORSO_HEIGHT, 0.5*(TORSO_WIDTH + UPPER_ARM_WIDTH)) *
		RotateZ(game.player.theta[LeftUpperArm]);

	game.player.theta[LeftLowerArm] -= 20;
	game.player.nodes[LeftLowerArm].transform = Translate(0.0, UPPER_ARM_HEIGHT, 0.0) * RotateZ(game.player.theta[LeftLowerArm]);

	game.player.theta[RightUpperLeg] -= 30;
	game.player.nodes[RightUpperLeg].transform = Translate(0.0, 0.0, -0.25*(TORSO_WIDTH + UPPER_LEG_WIDTH)) *
		RotateZ(game.player.theta[RightUpperLeg]);

	game.player.theta[LeftUpperLeg] += 10;
	game.player.nodes[LeftUpperLeg].transform = Translate(0.0, 0.0, 0.25*(TORSO_WIDTH + UPPER_LEG_WIDTH)) *
		RotateZ(game.player.theta[LeftUpperLeg]);

	glutTimerFunc(70, phase3, 1);
	glutPostRedisplay();
}

void phase1(int value)
{
	game.player.pos_x += 0.1;
	game.player.nodes[Torso].transform = Translate(game.player.pos_x, game.player.pos_y, 0.0);

	game.player.theta[RightUpperArm] += 10;
	game.player.nodes[RightUpperArm].transform = Translate(0.0, TORSO_HEIGHT, -0.5*(TORSO_WIDTH + UPPER_ARM_WIDTH)) *
		RotateZ(game.player.theta[RightUpperArm]);

	game.player.theta[RightLowerArm] += 20;
	game.player.nodes[RightLowerArm].transform = Translate(0.0, UPPER_ARM_HEIGHT, 0.0) * RotateZ(game.player.theta[RightLowerArm]);

	game.player.theta[LeftUpperArm] -= 10;
	game.player.nodes[LeftUpperArm].transform = Translate(0.0, TORSO_HEIGHT, 0.5*(TORSO_WIDTH + UPPER_ARM_WIDTH)) *
		RotateZ(game.player.theta[LeftUpperArm]);

	game.player.theta[LeftLowerArm] += 20;
	game.player.nodes[LeftLowerArm].transform = Translate(0.0, UPPER_ARM_HEIGHT, 0.0) * RotateZ(game.player.theta[LeftLowerArm]);

	game.player.theta[RightUpperLeg] -= 30;
	game.player.nodes[RightUpperLeg].transform = Translate(0.0, 0.0, -0.25*(TORSO_WIDTH + UPPER_LEG_WIDTH)) *
		RotateZ(game.player.theta[RightUpperLeg]);

	game.player.theta[RightLowerLeg] = 0;
	game.player.nodes[RightLowerLeg].transform = Translate(0.0, UPPER_LEG_HEIGHT, 0.0) * RotateZ(game.player.theta[RightLowerLeg]);

	game.player.theta[LeftUpperLeg] -= 30;
	game.player.nodes[LeftUpperLeg].transform = Translate(0.0, 0.0, 0.25*(TORSO_WIDTH + UPPER_LEG_WIDTH)) *
		RotateZ(game.player.theta[LeftUpperLeg]);

	glutTimerFunc(70, phase2, 1);
	glutPostRedisplay();
}

//키보드 조작함수 구현
void specialkeyboard(int key, int x, int y)
{
	float playery = game.player.pos_y + 0.92;
	int i;

	switch (key) {
	case GLUT_KEY_UP:
		if(game.player.pos_y < 0.8)
			game.player.pos_y += 0.222;
		if (game.treehere())
			game.player.pos_y -= 0.222;
		game.player.nodes[Torso].transform = Translate(game.player.pos_x, game.player.pos_y, 0.0);
		break;
	case GLUT_KEY_DOWN:
		if(game.player.pos_y > -0.8)
			game.player.pos_y -= 0.222;
		if (game.treehere())
			game.player.pos_y += 0.222;
		game.player.nodes[Torso].transform = Translate(game.player.pos_x, game.player.pos_y, 0.0);
		break;
	case GLUT_KEY_RIGHT:
		game.player.pos_x += 0.2;
		if (game.treehere())
		{
			game.player.pos_x -= 0.2;
			break;
		}

		i = (int)((game.player.pos_x + 0.9)* 10) / 2;
		if (game.map.map[i] != _river)
		{
			game.player.pos_y = (int)(playery / 0.222 + 0.5) * 0.222 - 0.888 - 0.025;
			if (game.map.map[i - 1] == _river)
 				game.player.pos_y -= game.map.river[i-1].log.speed * game.map.river[i-1].log.direc * 160;
		}
		else
		{
			for (int j = LOG_N - 1; j >= 0; j++)
			{
				float logy = game.map.river[i].log.log[j][0].y + game.map.river[i].log.lmove[j];
				if (game.player.pos_y < logy + game.map.river[i].log.width)
				{
					game.player.pos_y = (int)((playery - logy) / 0.222) * 0.222 + logy - 0.92 ;
					game.player.pos_y += game.map.river[i].log.speed * game.map.river[i].log.direc * 160;
					break;
				}
			}
		}

		game.player.pos_x -= 0.2;
		game.player.nodes[Torso].transform = Translate(game.player.pos_x, game.player.pos_y, 0.0);

		game.player.theta[RightUpperArm] += 20;
		game.player.nodes[RightUpperArm].transform = Translate(0.0, TORSO_HEIGHT, -0.5*(TORSO_WIDTH + UPPER_ARM_WIDTH)) *
			RotateZ(game.player.theta[RightUpperArm]);

		game.player.theta[LeftUpperArm] -= 20;
		game.player.nodes[LeftUpperArm].transform = Translate(0.0, TORSO_HEIGHT, 0.5*(TORSO_WIDTH + UPPER_ARM_WIDTH)) *
			RotateZ(game.player.theta[LeftUpperArm]);

		game.player.theta[RightUpperLeg] += 60;
		game.player.nodes[RightUpperLeg].transform = Translate(0.0, 0.0, -0.25*(TORSO_WIDTH + UPPER_LEG_WIDTH)) *
			RotateZ(game.player.theta[RightUpperLeg]);

		game.player.theta[RightLowerLeg] -= 90;
		game.player.nodes[RightLowerLeg].transform = Translate(0.0, UPPER_LEG_HEIGHT, 0.0) * RotateZ(game.player.theta[RightLowerLeg]);

		glutTimerFunc(70, phase1, 1);
		break;
	}

	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(700, 500);

	glutInitContextVersion(3, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutCreateWindow("Computer Graphics");

	glewInit();

	init();

	glutDisplayFunc(draw);
	glutIdleFunc(move);
	glutSpecialFunc(specialkeyboard);
	glutMainLoop();
	return 0;
}