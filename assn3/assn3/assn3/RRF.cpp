#include "RRF.h"

void ROAD::load()
{
	rigidroad[0] = vec3(0.0, 0.0, 0.0);
	rigidroad[1] = rigidroad[0] + vec3(0.0, 2.0, 0.0);
	rigidroad[2] = rigidroad[0] + vec3(0.2, 0.0, 0.0);
	rigidroad[3] = rigidroad[1]; rigidroad[4] = rigidroad[2];
	rigidroad[5] = rigidroad[3] + vec3(0.2, 0.0, 0.0);

	for (int i = 0; i < 6; i++)
		rigidcolor[i] = vec4(0.0, 0.0, 0.0, 1.0);

	glGenBuffers(1, &roadB);
	glBindBuffer(GL_ARRAY_BUFFER, roadB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rigidroad) + sizeof(rigidcolor), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(rigidroad), rigidroad);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(rigidroad), sizeof(rigidcolor), rigidcolor);

	car.load();
}

void ROAD::init(int* map, GLuint program)
{
	for (int i = 0; i < MAP_SIZE; i++)
		if (map[i] == _road)
			road[i] = vec3(0.2*i, 0.0, 0.0);
	//road[1] = road[0] + vec3(0.0, 2.0, 0.0);
	//road[2] = road[0] + vec3(0.2, 0.0, 0.0);
	//road[3] = road[1]; road[4] = road[2];
	//road[5] = road[3] + vec3(0.2, 0.0, 0.0);

	for (int i = 0; i < MAP_SIZE; i++)
	{
		vPosition[i] = glGetAttribLocation(program, "vPosition");
		glEnableVertexAttribArray(vPosition[i]);
		vColor[i] = glGetAttribLocation(program, "vColor");
		glEnableVertexAttribArray(vColor[i]);
	}

	car.init(map, program);
}

void ROAD::draw(GLint pro, GLint model)
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		mat4 n = Translate(-1.0 + road[i].x, -1.0 + road[i].y, 0.0 + road[i].z);
		glBindBuffer(GL_ARRAY_BUFFER, roadB);
		glVertexAttribPointer(vPosition[i], 3, GL_FLOAT, GL_FALSE, 0,
			BUFFER_OFFSET(0));
		glVertexAttribPointer(vColor[i], 4, GL_FLOAT, GL_FALSE, 0,
			BUFFER_OFFSET(sizeof(rigidroad)));
		glUniformMatrix4fv(model, 1, GL_TRUE, n);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
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

void FIELD::load()
{
	rigidfield[0] = vec3(0.0, 0.0, 0.0);
	rigidfield[1] = rigidfield[0] + vec3(0.0, 2.0, 0.0);
	rigidfield[2] = rigidfield[0] + vec3(0.2, 0.0, 0.0);
	rigidfield[3] = rigidfield[1]; rigidfield[4] = rigidfield[2];
	rigidfield[5] = rigidfield[3] + vec3(0.2, 0.0, 0.0);

	for (int i = 0; i < 6; i++)
		rigidcolor[i] = vec4(0.0, 0.8, 0.0, 1.0);

	glGenBuffers(1, &fieldB);
	glBindBuffer(GL_ARRAY_BUFFER, fieldB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rigidfield) + sizeof(rigidcolor), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(rigidfield), rigidfield);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(rigidfield), sizeof(rigidcolor), rigidcolor);

	tree.load();
}

void FIELD::init(int* map, GLuint program)
{
	for (int i = 0; i < MAP_SIZE; i++)
		if (map[i] == _field)
			field[i] = vec3(0.2*i, 0.0, 0.0);
	/*field[0] = vec3(0.2*num, 0.0, 0.0);
	field[1] = field[0] + vec3(0.0, 2.0, 0.0);
	field[2] = field[0] + vec3(0.2, 0.0, 0.0);
	field[3] = field[1]; field[4] = field[2];
	field[5] = field[3] + vec3(0.2, 0.0, 0.0);*/
	
	for (int i = 0; i < MAP_SIZE; i++)
	{
		vPosition[i] = glGetAttribLocation(program, "vPosition");
		glEnableVertexAttribArray(vPosition[i]);
		vColor[i] = glGetAttribLocation(program, "vColor");
		glEnableVertexAttribArray(vColor[i]);
	}

	tree.init(map, program);
}

void FIELD::draw(GLint pro, GLint model)
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		mat4 n = Translate(-1.0 + field[i].x, -1.0 + field[i].y, 0.0 + field[i].z);
		glBindBuffer(GL_ARRAY_BUFFER, fieldB);
		glVertexAttribPointer(vPosition[i], 3, GL_FLOAT, GL_FALSE, 0,
			BUFFER_OFFSET(0));
		glVertexAttribPointer(vColor[i], 4, GL_FLOAT, GL_FALSE, 0,
			BUFFER_OFFSET(sizeof(rigidfield)));
		glUniformMatrix4fv(model, 1, GL_TRUE, n);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	tree.draw(pro, model);
}