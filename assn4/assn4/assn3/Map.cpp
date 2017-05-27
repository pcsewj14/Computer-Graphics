#include "Map.h"

void MAP::load()
{
	road.load();
	field.load();

	line[0] = vec3(0.0, 0.0, 0.0);
	line[1] = line[0] + vec3(0.0, 0.2, 0.0);
	line[2] = line[0] + vec3(0.005, 0.0, 0.0);
	line[3] = line[1]; line[4] = line[2];
	line[5] = line[3] + vec3(0.005, 0.0, 0.0);

	for (int i = 0; i < 6; i++)
		color[i] = vec4(1, 1, 1, 1);

	tline.load("roadline.png");

	texture[0] = vec2(0.0, 0.0);
	texture[1] = vec2(0.0, 1.0);
	texture[2] = vec2(1.0, 1.0);
	texture[3] = vec2(0.0, 0.0);
	texture[4] = vec2(1.0, 1.0);
	texture[5] = vec2(1.0, 0.0);

	for (int i = 0; i < 6; i++)
		normal[i] = vec3(0.0, 0.0, 1.0);

	glGenBuffers(1, &lineB);
	glBindBuffer(GL_ARRAY_BUFFER, lineB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(line) + sizeof(color) + sizeof(texture) + sizeof(normal), NULL, GL_STATIC_DRAW);
	GLintptr offset = 0;
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(line), line);
	offset += sizeof(line);
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(color), color);
	offset += sizeof(color);
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(texture), texture);
	offset += sizeof(texture);
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(normal), normal);
}

void MAP::init(GLuint program)
{
	shininess = 100.0;
	map[0] = _field;
	for (int i = 1; i < MAP_SIZE; i++)
		map[i] = rand() % 2;

	for (int i = 0; i < MAP_SIZE; i++)
		for (int j = 0; j < 5; j++)
			rLine[i][j] = vec3(0.0, 0.0, 0.0);

	road.init(map, program);
	field.init(map, program);

	for (int i = 0; i < MAP_SIZE; i++)
		if (map[i] == _road)
		{
			if (map[i - 1] == _road)
			{
				for (int j = 0; j < 5; j++)
					rLine[i][j] = vec3(0.2*i, 0.4*j, 0.0);
			}
		}

	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	vTexture = glGetAttribLocation(program, "vTexCoord");
	glEnableVertexAttribArray(vTexture);
	vNormal = glGetAttribLocation(program, "vNormal");
	glEnableVertexAttribArray(vNormal);

	diffuse = glGetUniformLocation(program, "texture");

	glUniform4fv(glGetUniformLocation(program, "AmbientProduct"),
		1, road.car.light_ambient);
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"),
		1, road.car.light_diffuse);
	glUniform4fv(glGetUniformLocation(program, "SpecularProduct"),
		1, road.car.light_specular);
	glUniform4fv(glGetUniformLocation(program, "LightPosition"),
		1, road.car.light_position);

	glUniform1f(glGetUniformLocation(program, "Shininess"),
		shininess);
	glUniform1i(glGetUniformLocation(program, "mo"), road.car.mo);
}

void MAP::draw(GLint pro, GLint model)
{
	road.draw(map, pro, model);
	field.draw(map, pro, model);
	
	if (road.car.mo != 1)
	{
		glActiveTexture(GL_TEXTURE0);
		tline.bind();
		glUniform1i(diffuse, 0);
		for (int i = 0; i < MAP_SIZE; i++)
			for (int j = 0; j < 5; j++)
			{
				mat4 n = Translate(-1.0 + rLine[i][j].x, -1.0 + rLine[i][j].y, 0.005);
				glBindBuffer(GL_ARRAY_BUFFER, lineB);
				glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0,
					BUFFER_OFFSET(0));
				glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0,
					BUFFER_OFFSET(sizeof(line)));
				glVertexAttribPointer(vTexture, 2, GL_FLOAT, GL_FALSE, 0,
					BUFFER_OFFSET(sizeof(line) + sizeof(color)));
				glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0,
					BUFFER_OFFSET(sizeof(line) + sizeof(color) + sizeof(texture)));
				glUniformMatrix4fv(model, 1, GL_TRUE, n);
				glDrawArrays(GL_TRIANGLES, 0, 6);
			}
	}
}

void MAP::move()
{
	road.move();
}