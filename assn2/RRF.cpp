#include "RRF.h"

void ROAD::init(int num, GLuint program)
{
	road[0] = vec3(0.2*num, 0.0, 0.0);
	road[1] = road[0] + vec3(0.0, 2.0, 0.0);
	road[2] = road[0] + vec3(0.2, 0.0, 0.0);
	road[3] = road[1]; road[4] = road[2];
	road[5] = road[3] + vec3(0.2, 0.0, 0.0);

	for (int i = 0; i < 6; i++)
		road_color[i] = vec4(0.0, 0.0, 0.0, 1.0);

	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);

	car.init(num, program);
}

void ROAD::buffer()
{
	glGenBuffers(1, &roadB);
	glBindBuffer(GL_ARRAY_BUFFER, roadB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(road) + sizeof(road_color), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(road), road);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(road), sizeof(road_color), road_color);

	car.buffer();
}

void ROAD::draw(GLint pro, GLint model)
{
	glBindBuffer(GL_ARRAY_BUFFER, roadB);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sizeof(road)));
	glDrawArrays(GL_TRIANGLES, 0, 6);

	car.draw(pro, model);
}

void ROAD::move()
{
	car.move();
}

void RIVER::init(int num, GLuint program, float di)
{
	river[0] = vec3(0.2*num, 0.0, 0.0);
	river[1] = river[0] + vec3(0.0, 2.0, 0.0);
	river[2] = river[0] + vec3(0.2, 0.0, 0.0);
	river[3] = river[1]; river[4] =river[2];
	river[5] = river[3] + vec3(0.2, 0.0, 0.0);

	for (int i = 0; i < 6; i++)
		river_color[i] = vec4(0.2, 0.5, 1.0, 1.0);

	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);

	log.init(num, program, di);
}

void RIVER::buffer()
{
	glGenBuffers(1, &riverB);
	glBindBuffer(GL_ARRAY_BUFFER, riverB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(river) + sizeof(river_color), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(river), river);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(river), sizeof(river_color), river_color);

	log.buffer();
}

void RIVER::draw(GLint pro, GLint model)
{
	glBindBuffer(GL_ARRAY_BUFFER, riverB);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sizeof(river)));
	glDrawArrays(GL_TRIANGLES, 0, 6);
	
	log.draw(pro, model);
}

void RIVER::move()
{
	log.move();
}

void FIELD::init(int num, GLuint program)
{
	field[0] = vec3(0.2*num, 0.0, 0.0);
	field[1] = field[0] + vec3(0.0, 2.0, 0.0);
	field[2] = field[0] + vec3(0.2, 0.0, 0.0);
	field[3] = field[1]; field[4] = field[2];
	field[5] = field[3] + vec3(0.2, 0.0, 0.0);

	for (int i = 0; i < 6; i++)
		field_color[i] = vec4(0.0, 0.8, 0.0, 1.0);

	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);

	tree.init(num, program);
}

void FIELD::buffer()
{
	glGenBuffers(1, &fieldB);
	glBindBuffer(GL_ARRAY_BUFFER, fieldB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(field) + sizeof(field_color), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(field), field);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(field), sizeof(field_color), field_color);

	tree.buffer();
}

void FIELD::draw(GLint pro, GLint model)
{
	glBindBuffer(GL_ARRAY_BUFFER, fieldB);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sizeof(field)));
	glDrawArrays(GL_TRIANGLES, 0, 6);

	tree.draw(pro, model);
}