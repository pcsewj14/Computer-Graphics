#include "Map.h"

void MAP::init(GLuint program)
{
	map[0] = _field;
	for (int i = 1; i < MAP_SIZE; i++)
	{
		if (map[i - 1] == _field)
			map[i] = rand() % 2 + 1;
		else
			map[i] = rand() % 3;
	}
	for (int i = 0; i < MAP_SIZE * 10; i++)
	{
		rLine_color[i] = vec4(1.0, 1.0, 1.0, 1.0);
		rLine[i] = vec3(0.0, 0.0, 0.0);
	}

	for (int i = 0; i < MAP_SIZE; i++)
	{
		if (map[i] == _field)
			field[i].init(i, program);
		else if (map[i] == _road)
		{
			road[i].init(i, program);
			if (map[i - 1] == _road)
				for (int j = 0; j < 10; j++)
				{
					int index = 10 * i + j;
					rLine[index] = vec3(0.2*i, 0.2*j, 0.0);
				}
		}
		else
		{
			if (map[i - 1] == _river)
				di[i] = -di[i - 1];
			else
				di[i] = rand() % 2 - 0.5;
			river[i].init(i, program, di[i]);
		}
	}

	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
}

void MAP::buffer()
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		if (map[i] == _field)
			field[i].buffer();
		else if (map[i] == _road)
			road[i].buffer();
		else
			river[i].buffer();
	}

	glGenBuffers(1, &lineB);
	glBindBuffer(GL_ARRAY_BUFFER, lineB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rLine) + sizeof(rLine_color), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(rLine), rLine);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(rLine), sizeof(rLine_color), rLine_color);
}

void MAP::draw(GLint pro, GLint model)
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		mat4 n = Translate(-1.0, -1.0, 0.0);
		glUniformMatrix4fv(model, 1, GL_TRUE, n);

		if (map[i] == _field)
			field[i].draw(pro, model);
		else if (map[i] == _road)
			road[i].draw(pro, model);
		else
			river[i].draw(pro, model);
	}

	mat4 n = Translate(-1.0, -1.0, 0.0);
	glUniformMatrix4fv( model, 1, GL_TRUE, n);
	glBindBuffer(GL_ARRAY_BUFFER, lineB);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sizeof(rLine)));
	glDrawArrays(GL_LINES, 0, MAP_SIZE * 10);
}

void MAP::move()
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		if (map[i] == _road)
			road[i].move();
		else if (map[i] == _river)
			river[i].move();
	}
}