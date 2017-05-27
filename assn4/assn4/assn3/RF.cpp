#include "RF.h"

void ROAD::load()
{
	troad.load("black.png");

	rigidroad[0] = vec3(0.0, 0.0, 0.0);
	rigidroad[1] = rigidroad[0] + vec3(0.0, 2.0, 0.0);
	rigidroad[2] = rigidroad[0] + vec3(0.2, 0.0, 0.0);
	rigidroad[3] = rigidroad[1]; rigidroad[4] = rigidroad[2];
	rigidroad[5] = rigidroad[3] + vec3(0.2, 0.0, 0.0);

	for (int i = 0; i < 6; i++)
	{
		rigidcolor[i] = vec4(1.0, 1.0, 1.0, 1.0);
		normal[i] = vec3(0.0, 0.0, 1.0);
	}

	texture[0] = vec2(0, 0);
	texture[1] = vec2(0, 1);
	texture[2] = vec2(1, 0);
	texture[3] = texture[0];
	texture[4] = texture[1];
	texture[5] = texture[2];

	glGenBuffers(1, &roadB);
	glBindBuffer(GL_ARRAY_BUFFER, roadB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rigidroad) + sizeof(rigidcolor) + sizeof(texture) + sizeof(normal) , NULL, GL_STATIC_DRAW);
	GLintptr offset = 0;
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(rigidroad), rigidroad);
	offset += sizeof(rigidroad);
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(rigidcolor), rigidcolor);
	offset += sizeof(rigidcolor);
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(texture), texture);
	offset += sizeof(texture);
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(normal), normal);

	car.load();
}

void ROAD::init(int* map, GLuint program)
{
	for (int i = 0; i < MAP_SIZE; i++)
		if (map[i] == _road)
			road[i] = vec3(0.2*i, 0.0, 0.0);
	
	for (int i = 0; i < MAP_SIZE; i++)
	{
		vPosition[i] = glGetAttribLocation(program, "vPosition");
		glEnableVertexAttribArray(vPosition[i]);
		vColor[i] = glGetAttribLocation(program, "vColor");
		glEnableVertexAttribArray(vColor[i]);
		vtexture[i] = glGetAttribLocation(program, "vTexCoord");
		glEnableVertexAttribArray(vtexture[i]);
		vNormal[i] = glGetAttribLocation(program, "vNormal");
		glEnableVertexAttribArray(vNormal[i]);
	}
	diffuse = glGetUniformLocation(program, "texture");

	car.init(map, program);
}

void ROAD::draw(int* map, GLint pro, GLint model)
{
	if (car.mo != 1)
	{
		for (int i = 0; i < MAP_SIZE; i++)
		{
			if (map[i] == _road)
			{
				glActiveTexture(GL_TEXTURE0);
				troad.bind();
				glUniform1i(diffuse, 0);
				mat4 n = Translate(-1.0 + road[i].x, -1.0 + road[i].y, 0.0 + road[i].z);
				glBindBuffer(GL_ARRAY_BUFFER, roadB);
				glVertexAttribPointer(vPosition[i], 3, GL_FLOAT, GL_FALSE, 0,
					BUFFER_OFFSET(0));
				glVertexAttribPointer(vColor[i], 4, GL_FLOAT, GL_FALSE, 0,
					BUFFER_OFFSET(sizeof(rigidroad)));
				glVertexAttribPointer(vtexture[i], 2, GL_FLOAT, GL_FALSE, 0,
					BUFFER_OFFSET(sizeof(rigidroad) + sizeof(rigidcolor)));
				glVertexAttribPointer(vNormal[i], 3, GL_FLOAT, GL_FALSE, 0,
					BUFFER_OFFSET(sizeof(rigidroad) + sizeof(rigidcolor) + sizeof(texture)));
				glUniformMatrix4fv(model, 1, GL_TRUE, n);
				glDrawArrays(GL_TRIANGLES, 0, 6);
			}
		}
	}

	car.draw(map, pro, model);
}

void ROAD::move()
{
	car.move();
}

void FIELD::load()
{
	tfield.load("field.png");
	rigidfield[0] = vec3(0.0, 0.0, 0.0);
	rigidfield[1] = rigidfield[0] + vec3(0.0, 2.0, 0.0);
	rigidfield[2] = rigidfield[0] + vec3(0.2, 0.0, 0.0);
	rigidfield[3] = rigidfield[1]; rigidfield[4] = rigidfield[2];
	rigidfield[5] = rigidfield[3] + vec3(0.2, 0.0, 0.0);

	texture[0] = vec2(0, 0);
	texture[1] = vec2(0, 1);
	texture[2] = vec2(1, 0);
	texture[3] = texture[0];
	texture[4] = texture[1];
	texture[5] = texture[2];

	for (int i = 0; i < 6; i++)
	{
		rigidcolor[i] = vec4(1.0, 1.0, 1.0, 1.0);
		normal[i] = vec3(0.0, 0.0, 1.0);
	}
	glGenBuffers(1, &fieldB);
	glBindBuffer(GL_ARRAY_BUFFER, fieldB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rigidfield) + sizeof(rigidcolor) + sizeof(texture) + sizeof(normal), NULL, GL_STATIC_DRAW);
	GLintptr offset = 0;
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(rigidfield), rigidfield);
	offset += sizeof(rigidfield);
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(rigidcolor), rigidcolor);
	offset += sizeof(rigidcolor);
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(texture), texture);
	offset += sizeof(texture);
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(normal), normal);

	tree.load();
}

void FIELD::init(int* map, GLuint program)
{
	for (int i = 0; i < MAP_SIZE; i++)
		if (map[i] == _field)
			field[i] = vec3(0.2*i, 0.0, 0.0);
	
	for (int i = 0; i < MAP_SIZE; i++)
	{
		vPosition[i] = glGetAttribLocation(program, "vPosition");
		glEnableVertexAttribArray(vPosition[i]);
		vColor[i] = glGetAttribLocation(program, "vColor");
		glEnableVertexAttribArray(vColor[i]);
		vtexture[i] = glGetAttribLocation(program, "vTexCoord");
		glEnableVertexAttribArray(vtexture[i]);
		vNormal[i] = glGetAttribLocation(program, "vNormal");
		glEnableVertexAttribArray(vNormal[i]);
	}
	diffuse = glGetUniformLocation(program, "texture");

	tree.init(map, program);
}

void FIELD::draw(int* map, GLint pro, GLint model)
{
	if (tree.mo != 1)
	{
		for (int i = 0; i < MAP_SIZE; i++)
		{
			if (map[i] == _field)
			{
				glActiveTexture(GL_TEXTURE0);
				tfield.bind();
				glUniform1i(diffuse, 0);
				mat4 n = Translate(-1.0 + field[i].x, -1.0 + field[i].y, 0.0 + field[i].z);
				glBindBuffer(GL_ARRAY_BUFFER, fieldB);
				glVertexAttribPointer(vPosition[i], 3, GL_FLOAT, GL_FALSE, 0,
					BUFFER_OFFSET(0));
				glVertexAttribPointer(vColor[i], 4, GL_FLOAT, GL_FALSE, 0,
					BUFFER_OFFSET(sizeof(rigidfield)));
				glVertexAttribPointer(vtexture[i], 2, GL_FLOAT, GL_FALSE, 0,
					BUFFER_OFFSET(sizeof(rigidfield) + sizeof(rigidcolor)));
				glVertexAttribPointer(vNormal[i], 3, GL_FLOAT, GL_FALSE, 0,
					BUFFER_OFFSET(sizeof(rigidfield) + sizeof(rigidcolor) + sizeof(texture)));
				glUniformMatrix4fv(model, 1, GL_TRUE, n);
				glDrawArrays(GL_TRIANGLES, 0, 6);
			}
		}
	}

	tree.draw(map, pro, model);
}