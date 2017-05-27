#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <ctime>
#include <cstdlib>

#define MAP_SIZE 30
#define CAR 5
#define LOG 3

enum MapType { field, road, river };
float moving = 0;

typedef struct rect {
	float x;
	float y;
	float width;
	float height;
	int type;
} rect;
rect character;
rect map[MAP_SIZE];
rect tree[MAP_SIZE][10];

typedef struct move {
	float x;
	float y;
	float space;
	float width;
	float height;
	float speed;
	float direction;
} move;
move car[MAP_SIZE][CAR];
move log[MAP_SIZE][LOG];

typedef struct vertex {
	float x;
	float y;
} vertex;
vertex roadline[10 * MAP_SIZE];

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	character.x = 0.015;
	character.y = 0.444;
	character.width = 0.1;
	character.height = 0.07;

	for (int i = 0; i < MAP_SIZE; i++)
	{
		map[i].x = i*0.1;
		map[i].y = 0;
		map[i].width = 1;
		map[i].height = 0.1;

		if (i == 0)
			map[i].type = field;
		else if (map[i - 1].type == field)
			map[i].type = rand() % 2 + 1;
		else
			map[i].type = rand() % 3;
	}

	for (int i = 0; i < 10 * MAP_SIZE; i++)
	{
		roadline[i].x = 0;
		roadline[i].y = 0;
	}

	int j = 0;
	for (int i = 1; i < MAP_SIZE; i++)
	{
		if (map[i].type == road && map[i - 1].type == road)
		{
			for (; j < 10 * i; j++)
			{
				roadline[j].x = map[i].x;
				roadline[j].y = 0.12*(j % 10);
			}
		}
	}

	for (int i = 1; i < MAP_SIZE; i++)
	{
		if (map[i].type == field)
		{
			int num = 0;
			for (int j = 0; j < 10; j++)
			{
				int chance = rand() % 4;

				if (chance == 0 /*&& num < 5*/)
				{
					num++;
					tree[i][j].x = map[i].x + 0.01;
					tree[i][j].y = j*0.111;
					tree[i][j].width = 0.1;
					tree[i][j].height = 0.08;
				}

				else
				{
					tree[i][j].x = 0;
					tree[i][j].y = 0;
					tree[i][j].width = 0;
					tree[i][j].height = 0;
				}
			}
		}
	}

	for (int i = 1; i < MAP_SIZE; i++)
	{
		if (map[i].type == road)
		{
			float _space = rand() % 3 * 0.1 + 0.3;
			float _speed = rand() % 5 * 0.00001 + 0.0003;
			float _direction = rand() % 2 - 0.5;
			for (int j = 0; j < CAR; j++)
			{
				car[i][j].x = map[i].x + 0.01;
				car[i][j].space = _space;
				car[i][j].width = 0.1;
				car[i][j].height = 0.08;
				car[i][j].speed = _speed;
				car[i][j].direction = _direction;
				car[i][j].y = 1 - (j*car[i][j].width + j*car[i][j].space);
				//속도는 speed*direction
			}
		}
	}

	for (int i = 1; i < MAP_SIZE; i++)
	{
		if (map[i].type == river)
		{
			float _space = rand() % 3 * 0.111 + 0.333;
			float _speed = rand() % 5 * 0.00001 + 0.0003;
			float _width = rand() % 3 * 0.111 + 0.333;
			float _direction;
			if (map[i - 1].type == river)
				_direction = -log[i - 1][0].direction;
				else
					_direction = rand() % 2 - 0.5;
			for (int j = 0; j < LOG; j++)
			{
				log[i][j].x = map[i].x + 0.01;
				log[i][j].space = _space;
				log[i][j].width = _width;
				log[i][j].height = 0.08;
				log[i][j].speed = _speed;
				log[i][j].direction = _direction;
				log[i][j].y = 1 - (j*log[i][j].width + j*log[i][j].space);
			}
		}
	}
}

void displayCar()
{
	glColor3f(0.5, 0.5, 0.5);
	glLoadIdentity();
	for (int i = 1; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < CAR; j++)
		{
			if (map[i].type == road)
			{
				glLoadIdentity();
				glTranslatef(car[i][j].x, car[i][j].y, 0.0);
				glBegin(GL_POLYGON);
				glVertex2f(0.0, 0.0);
				glVertex2f(0.0, car[i][j].width);
				glVertex2f(car[i][j].height, car[i][j].width);
				glVertex2f(car[i][j].height, 0.0);
				glEnd();
			}
		}
	}
}

void displayLog()
{
	glColor3f(0.4, 0.2, 0.1);
	glLoadIdentity();
	for (int i = 1; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < LOG; j++)
		{
			if (map[i].type == river)
			{
				glLoadIdentity();
				glTranslatef(log[i][j].x, log[i][j].y, 0.0);
				glBegin(GL_POLYGON);
				glVertex2f(0.0, 0.0);
				glVertex2f(0.0, log[i][j].width);
				glVertex2f(log[i][j].height, log[i][j].width);
				glVertex2f(log[i][j].height, 0.0);
				glEnd();
			}
		}
	}
}

void displayCharacter()
{
	glLoadIdentity();
	glTranslatef(character.x, character.y, 0);

	glColor3f(0.9, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(0, character.width);
	glVertex2f(character.height, character.width);
	glVertex2f(character.height, 0);
	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < MAP_SIZE; i++)
	{
		if (map[i].type == field)
			glColor3f(0, 0.8, 0);
		else if (map[i].type == road)
			glColor3f(0, 0, 0);
		else
			glColor3f(0.2, 0.5, 1);
		glLoadIdentity();
		glTranslatef(map[i].x, map[i].y, 0.0);
		glBegin(GL_POLYGON);
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, map[i].width);
		glVertex2f(map[i].height, map[i].width);
		glVertex2f(map[i].height, 0.0);
		glEnd();
	}

	glColor3f(1, 1, 1);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	for (int i = 0; i < 10 * MAP_SIZE; i++)
		glVertex2f(roadline[i].x, roadline[i].y);
	glEnd();

	glColor3f(0.5, 0.3, 0.2);
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (map[i].type == field)
			{
				glLoadIdentity();
				glTranslatef(tree[i][j].x, tree[i][j].y, 0.0);
				glBegin(GL_POLYGON);
				glVertex2f(0.0, 0.0);
				glVertex2f(0.0, tree[i][j].width);
				glVertex2f(tree[i][j].height, tree[i][j].width);
				glVertex2f(tree[i][j].height, 0.0);
				glEnd();
			}
		}
	}

	displayCar();
	displayLog();
	displayCharacter();

	glutSwapBuffers();
}

void timer(int vlaue)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(moving, 1 + moving, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	moving += 0.001;

	glutTimerFunc(30, timer, 0);
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void reInitCL()
{
	for (int i = 1; i < MAP_SIZE; i++)
	{	
		if (map[i].type == road)
		{
			if (car[i][0].direction > 0)
			{
				for (int j = 0; j < CAR; j++)
					if (car[i][j].y >= (CAR - 1) * car[i][0].width + CAR * car[i][0].space)
						car[i][j].y = -car[i][0].width;
						
			}
			else
			{
				for (int j = 0; j < CAR; j++)
					if (car[i][j].y <= 1 - (CAR * car[i][0].width + CAR * car[i][0].space))
						car[i][j].y = 1;
			}
		}

		if (map[i].type == river)
		{
			if (log[i][0].direction > 0)
			{
				for (int j = 0; j < LOG; j++)
					if (log[i][j].y >= (LOG - 1) * log[i][0].width + LOG * log[i][0].space)
						log[i][j].y = -log[i][0].width;

			}
			else
			{
				for (int j = 0; j < LOG; j++)
					if (log[i][j].y <= 1 - (LOG * log[i][0].width + LOG * log[i][0].space))
						log[i][j].y = 1;
			}
		}
	}
}	//차가 무한히 나오도록

bool crushed()
{
	int i = (int)(character.x * 10);
	if (i >= MAP_SIZE) return true;
	for (int j = 0; j < CAR; j++)
	{
		if ((car[i][j].y < character.y + character.width
			&& character.y + character.width < car[i][j].y + car[i][j].width)
			|| (car[i][j].y < character.y
				&& character.y < car[i][j].y + car[i][j].width))
			return true;
	}
	if (moving > character.x + character.height)
		return true;
	if (character.y <= -character.width || character.y >= 1)
		return true;

	for (int j = 0; j < LOG; j++)
	{
		if ((log[i][j].y < character.y + character.width
			&& character.y + character.width < log[i][j].y + log[i][j].width)
			&& (log[i][j].y < character.y
				&& character.y < log[i][j].y + log[i][j].width))
			return false;
	}
	if (map[i].type == river)
		return true;

	return false;
}	  //충돌검사

void moveCL()
{
	for (int i = 1; i < MAP_SIZE; i++)
	{
		if (map[i].type == road)
		{
			for (int j = 0; j < CAR; j++)
				car[i][j].y += car[i][j].speed * car[i][j].direction;
		}

		if (map[i].type == river)
		{
			for (int j = 0; j < LOG; j++)
				log[i][j].y += log[i][j].speed * log[i][j].direction;
			if ((int)(character.x * 10) == i)
				character.y += log[i][0].speed * log[i][0].direction;
		}
		reInitCL();
		if (crushed()) exit(0);
	}
	glutPostRedisplay();
}

bool IsThereTree()
{
	int i = character.x / 0.1;   /*좌표 계산 수정 필요*/
	int j = character.y / 0.111;

	if (tree[i][j].x == 0)
		return false;
	else
		return true;
}

void specialkeyboard(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		if (character.y < 0.9 - character.width)
			character.y += 0.111;
		if (crushed()) exit(0);
		if (IsThereTree())
			character.y -= 0.111;
		break;
	case GLUT_KEY_DOWN:
		if (character.y > character.width)
			character.y -= 0.111;
		if (crushed()) exit(0);
		if (IsThereTree())
			character.y += 0.111;
		break;
	case GLUT_KEY_RIGHT:
		character.x += 0.1;
		if (IsThereTree())
		{
			character.x -= 0.1;
			break;
		}
		int i = (int)(character.x * 10);
		if(map[i].type != river)
			character.y = (int)(character.y / 0.111 + 0.5) * 0.111;
		else
		{
			for (int j = LOG - 1; j >= 0; j++)
			{
				if (character.y < log[i][j].y + log[i][j].width)
					character.y = (int)((character.y - log[i][j].y) / 0.111 - 0.5) * 0.111 + log[i][j].y +0.001;
				break;
			}
		}
		if (crushed()) exit(0);
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(700, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	timer(0);
	glutIdleFunc(moveCL);
	glutSpecialFunc(specialkeyboard);
	glutMainLoop();
	return 0;
}