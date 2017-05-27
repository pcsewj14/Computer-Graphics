#include "CLT.h"

void CAR::init(int num, GLuint program)
{
	width = 0.2;
	vec3 car_hw[2] = { vec3(0.16,0.0,0.0), vec3(0.0,0.2,0.0) };
	space = rand() % 3 * 0.2 + 0.6;
	speed = rand() % 5 * 0.0001 + 0.0006;
	direc = rand() % 2 - 0.5;
	for (int i = 0; i < CAR_N; i++)
		cmove[i] = 0;

	for (int i = 0; i < CAR_N; i++)
	{
		car[i][0] = vec3(0.2*num + 0.02, 2 - i*(space + 0.2), 0.0);
		car[i][1] = car[i][0] + car_hw[1];
		car[i][2] = car[i][0] + car_hw[0];
		car[i][3] = car[i][1]; car[i][4] = car[i][2];
		car[i][5] = car[i][3] + car_hw[0];
	}
	for (int i = 0; i < CAR_N; i++)
		for (int j = 0; j < 6; j++)
			car_color[i][j] = vec4(0.5, 0.5, 0.5, 1.0);

	for (int i = 0; i < CAR_N; i++)
	{
		vPosition[i] = glGetAttribLocation(program, "vPosition");
		glEnableVertexAttribArray(vPosition[i]);
		vColor[i] = glGetAttribLocation(program, "vColor");
		glEnableVertexAttribArray(vColor[i]);
	}
}

void CAR::buffer()
{
	for (int i = 0; i < CAR_N; i++)
	{
		glGenBuffers(1, &carB[i]);
		glBindBuffer(GL_ARRAY_BUFFER, carB[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(car[i]) + sizeof(car_color[i]), NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(car[i]), car[i]);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(car[i]), sizeof(car_color[i]), car_color[i]);
	}
}

void CAR::draw(GLint pro, GLint model)
{
	for (int i = 0; i < CAR_N; i++)
	{
		mat4 n = Translate(-1.0, -1.0 + cmove[i], 0.0);
		glBindBuffer(GL_ARRAY_BUFFER, carB[i]);
		glVertexAttribPointer(vPosition[i], 3, GL_FLOAT, GL_FALSE, 0,
			BUFFER_OFFSET(0));
		glVertexAttribPointer(vColor[i], 4, GL_FLOAT, GL_FALSE, 0,
			BUFFER_OFFSET(sizeof(car[i])));
		glUniformMatrix4fv(model, 1, GL_TRUE, n);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}

void CAR::reInit()
{
	float com = (CAR_N - 1)*0.2 + CAR_N*space;
	if (direc > 0)
	{
		for (int i = 0; i < CAR_N; i++)
			if (cmove[i] - i*(space + 0.2) >= com - 2)
				cmove[i] = i*(space + 0.2) - 2.2;
	}
	else
	{
		float com = 2 - CAR_N * (0.2 + space);
		for (int i = 0; i < CAR_N; i++)
			if (cmove[i] - i*(space + 0.2) <= com - 2)
				cmove[i] = i*(space + 0.2);
	}
}

void CAR::move()
{
	for (int i = 0; i < CAR_N; i++)
		cmove[i] += speed*direc;
	reInit();
}

void LOG::init(int num, GLuint program, float di)
{
	vec3 h = vec3(0.16, 0.0, 0.0);
	space = rand() % 3 * 0.222 + 0.666;
	speed = rand() % 5 * 0.00015 + 0.0006;
	direc = di;
	width = rand() % 3 * 0.222 + 0.666;
	for (int i = 0; i < LOG_N; i++)
		lmove[i] = 0;

	for (int i = 0; i < LOG_N; i++)
	{
		log[i][0] = vec3(0.2*num + 0.02, 2 - i*(space + width), 0.0);
		log[i][1] = log[i][0] + vec3(0.0, width, 0.0);
		log[i][2] = log[i][0] + h;
		log[i][3] = log[i][1]; log[i][4] = log[i][2];
		log[i][5] = log[i][3] + h;
	}
	for (int i = 0; i < LOG_N; i++)
		for (int j = 0; j < 6; j++)
			log_color[i][j] = vec4(0.4, 0.2, 0.1, 1.0);

	for (int i = 0; i < LOG_N; i++)
	{
		vPosition[i] = glGetAttribLocation(program, "vPosition");
		glEnableVertexAttribArray(vPosition[i]);
		vColor[i] = glGetAttribLocation(program, "vColor");
		glEnableVertexAttribArray(vColor[i]);
	}
}

void LOG::buffer()
{
	for (int i = 0; i < LOG_N; i++)
	{
		glGenBuffers(1, &logB[i]);
		glBindBuffer(GL_ARRAY_BUFFER, logB[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(log[i]) + sizeof(log_color[i]), NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(log[i]), log[i]);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(log[i]), sizeof(log_color[i]), log_color[i]);
	}
}

void LOG::draw(GLint pro, GLint model)
{
	for (int i = 0; i < LOG_N; i++)
	{
		mat4 n = Translate(-1.0, -1.0 + lmove[i], 0.0);
		glBindBuffer(GL_ARRAY_BUFFER, logB[i]);
		glVertexAttribPointer(vPosition[i], 3, GL_FLOAT, GL_FALSE, 0,
			BUFFER_OFFSET(0));
		glVertexAttribPointer(vColor[i], 4, GL_FLOAT, GL_FALSE, 0,
			BUFFER_OFFSET(sizeof(log[i])));
		glUniformMatrix4fv(model, 1, GL_TRUE, n);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}

void LOG::reInit()
{
	if (direc > 0)
	{
		float com = (LOG_N - 1)*width + LOG_N*space;
		for (int i = 0; i < LOG_N; i++)
			if (lmove[i] - i*(space + width) >= com - 2)
				lmove[i] = i*(space + width) - (2 + width);
	}
	else
	{
		float com = 2 - LOG_N * (width + space);
		for (int i = 0; i < LOG_N; i++)
			if (lmove[i] - i*(space + width) <= com - 2)
				lmove[i] = i*(space + width);
	}
}

void LOG::move()
{
	for (int i = 0; i < LOG_N; i++)
		lmove[i] += speed*direc;
	reInit();
}

void TREE::init(int num, GLuint program)
{
	if (num == 0)
	{
		for (int i = 0; i < 10; i++)
		{
			tree[i][0] = vec3(0, 0, 0.0);
			tree[i][1] = tree[i][0]; tree[i][2] = tree[i][0];
			tree[i][3] = tree[i][0]; tree[i][4] = tree[i][0];
			tree[i][5] = tree[i][0];
		}
	}
	else
	{
		vec3 tree_hw[2] = { vec3(0.16,0.0,0.0), vec3(0.0,0.2,0.0) };
		int ran = 0;
		for (int i = 0; i < 10; i++)
		{
			int chance = rand() % 4;
			if (chance == 0)
			{
				ran++;
				tree[i][0] = vec3(0.2*num + 0.02, i*0.222, 0.0);
				tree[i][1] = tree[i][0] + tree_hw[1];
				tree[i][2] = tree[i][0] + tree_hw[0];
				tree[i][3] = tree[i][1]; tree[i][4] = tree[i][2];
				tree[i][5] = tree[i][3] + tree_hw[0];
			}
			else
			{
				for (int j = 0; j < 6; j++)
					tree[i][j] = vec3(0.0, 0.0, 0.0);
			}
		}
	}
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 6; j++)
			tree_color[i][j] = vec4(0.5, 0.3, 0.2, 1.0);

	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
}

void TREE::buffer()
{
	glGenBuffers(1, &treeB);
	glBindBuffer(GL_ARRAY_BUFFER, treeB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tree) + sizeof(tree_color), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(tree), tree);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(tree), sizeof(tree_color), tree_color);
}

void TREE::draw(GLint pro, GLint model)
{
	glBindBuffer(GL_ARRAY_BUFFER, treeB);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sizeof(tree)));
	glDrawArrays(GL_TRIANGLES, 0, 60);
}