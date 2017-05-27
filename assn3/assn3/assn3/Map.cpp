#include "Map.h"

void MAP::load()
{
	road.load();
	field.load();
}

void MAP::init(GLuint program)
{
	map[0] = _field;
	for (int i = 1; i < MAP_SIZE; i++)
	{
		/*if (map[i - 1] == _field)
			map[i] = rand() % 2 + 1;
		else*/
			map[i] = rand() % 2;
	}								//river는 안나오도록 했음
	for (int i = 0; i < MAP_SIZE * 10; i++)
	{
		rLine_color[i] = vec4(1.0, 1.0, 1.0, 1.0);
		rLine[i] = vec3(0.0, 0.0, 0.0);
	}

	field.init(map, program);
	road.init(map, program);
	for (int i = 0; i < MAP_SIZE; i++)
	{
		 if (map[i] == _road)
		 {
			if (map[i - 1] == _road)
				for (int j = 0; j < 10; j++)
				{
					int index = 10 * i + j;
					rLine[index] = vec3(0.2*i, 0.2*j, 0.0);
				}
		}
		/*else
		{
			if (map[i - 1] == _river)
				di[i] = -di[i - 1];
			else
				di[i] = rand() % 2 - 0.5;
			river[i].init(i, program, di[i]);
		}*/
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
		if(map[i] == _river)
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

		if(map[i] == _river)
			river[i].draw(pro, model);
	}
	field.draw(pro, model);
	road.draw(pro, model);

	mat4 n = Translate(-1.0, -1.0, 0.001);
	glBindBuffer(GL_ARRAY_BUFFER, lineB);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sizeof(rLine)));
	glUniformMatrix4fv( model, 1, GL_TRUE, n);
	glDrawArrays(GL_LINES, 0, MAP_SIZE * 10);
}

void MAP::move()
{
	road.move();
	for (int i = 0; i < MAP_SIZE; i++)
	{
		
		if (map[i] == _river)
			river[i].move();
	}
}