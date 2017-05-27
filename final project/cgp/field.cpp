#include "field.h"

void ROAD::load()
{
	tex.load("road.png");
	ltex.load("line.png");

	vertex[0] = vec3(0, 0, 0);
	vertex[1] = vertex[0] + vec3(0, 10, 0);
	vertex[2] = vertex[0] + vec3(2, 0, 0);
	vertex[3] = vertex[1]; vertex[4] = vertex[2];
	vertex[5] = vertex[3] + vec3(2, 0, 0);

	lvertex[0] = vec3(0, 0, 0);
	lvertex[1] = lvertex[0] + vec3(0, 10, 0);
	lvertex[2] = lvertex[0] + vec3(0.1, 0, 0);
	lvertex[3] = lvertex[1]; lvertex[4] = lvertex[2];
	lvertex[5] = lvertex[3] + vec3(0.1, 0, 0);

	for (int i = 0; i < 6; i++)
		color[i] = vec4(1, 1, 1, 1);

	texture[0] = vec2(0, 0);
	texture[1] = vec2(0, 1);
	texture[2] = vec2(1, 0);
	texture[3] = texture[1];
	texture[4] = texture[2];
	texture[5] = vec2(1, 1);

	glGenBuffers(1, &buffer[0]);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex)+ sizeof(color) + sizeof(texture), NULL, GL_STATIC_DRAW);
	GLintptr offset = 0;
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vertex), vertex);
	offset += sizeof(vertex);
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(color), color);
	offset += sizeof(color);
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(texture), texture);

	glGenBuffers(1, &buffer[1]);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lvertex) + sizeof(color) + sizeof(texture), NULL, GL_STATIC_DRAW);
	offset = 0;
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(lvertex), lvertex);
	offset += sizeof(lvertex);
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(color), color);
	offset += sizeof(color);
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(texture), texture);
}

void FIELD::load()
{
	tex.load("field.png");

	vertex[0] = vec3(0, 0, 0);
	vertex[1] = vertex[0] + vec3(0, 10, 0);
	vertex[2] = vertex[0] + vec3(0.5, 0, 0);
	vertex[3] = vertex[1]; vertex[4] = vertex[2];
	vertex[5] = vertex[3] + vec3(0.5, 0, 0);

	for (int i = 0; i < 6; i++)
		color[i] = vec4(1, 1, 1, 1);

	texture[0] = vec2(0, 0);
	texture[1] = vec2(0, 1);
	texture[2] = vec2(1, 0);
	texture[3] = texture[1];
	texture[4] = texture[2];
	texture[5] = vec2(1, 1);

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) + sizeof(color) + sizeof(texture), NULL, GL_STATIC_DRAW);
	GLintptr offset = 0;
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vertex), vertex);
	offset += sizeof(vertex);
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(color), color);
	offset += sizeof(color);
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(texture), texture);
}

void GRASS::load()
{
	tex.load("grass.png");

	vertex[0] = vec3(0, 0, 0);
	vertex[1] = vertex[0] + vec3(0, 10, 0);
	vertex[2] = vertex[0] + vec3(2, 0, 0);
	vertex[3] = vertex[1]; vertex[4] = vertex[2];
	vertex[5] = vertex[3] + vec3(2, 0, 0);

	for (int i = 0; i < 6; i++)
		color[i] = vec4(1, 1, 1, 1);

	texture[0] = vec2(0, 0);
	texture[1] = vec2(0, 1);
	texture[2] = vec2(1, 0);
	texture[3] = texture[1];
	texture[4] = texture[2];
	texture[5] = vec2(1, 1);

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) + sizeof(color) + sizeof(texture), NULL, GL_STATIC_DRAW);
	GLintptr offset = 0;
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vertex), vertex);
	offset += sizeof(vertex);
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(color), color);
	offset += sizeof(color);
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(texture), texture);
}

void TREE::load()
{
	tex.load("tree.png");
	int vcount = 1; int tcount = 1; fcount = 0;

	vec2 ftexture[142];
	vec3 fvertex[77];

	ifstream f("tree.obj");

	while (!f.eof())
	{
		string buf;
		getline(f, buf);

		if (buf.length() == 0)
			continue;

		vector<string> t = tokenize(buf, " ");
		string flag = t[0];

		if (flag.compare("#") == 0)
			continue;
		else if (flag.compare("v") == 0)
			fvertex[vcount++] = vec3(stof(t[1]), stof(t[2]), stof(t[3]));
		else if (flag.compare("vt") == 0)
			ftexture[tcount++] = vec2(stof(t[1]), stof(t[2]));
		else if (flag.compare("f") == 0)
		{
			vector<string> p1 = tokenize(t[1], "/");
			vector<string> p2 = tokenize(t[2], "/");
			vector<string> p3 = tokenize(t[3], "/");
			vector<string> p4;
			if (t.size() == 5)
				p4 = tokenize(t[4], "/");

			vertex[fcount][0] = fvertex[stoi(p1[0])];
			vertex[fcount][1] = fvertex[stoi(p2[0])];
			vertex[fcount][2] = fvertex[stoi(p3[0])];

			texture[fcount][0] = ftexture[stoi(p1[1])];
			texture[fcount][1] = ftexture[stoi(p2[1])];
			texture[fcount++][2] = ftexture[stoi(p3[1])];

			if (t.size() == 5)
			{
				vertex[fcount][0] = fvertex[stoi(p3[0])];
				vertex[fcount][1] = fvertex[stoi(p4[0])];
				vertex[fcount][2] = fvertex[stoi(p1[0])];

				texture[fcount][0] = ftexture[stoi(p3[1])];
				texture[fcount][1] = ftexture[stoi(p4[1])];
				texture[fcount++][2] = ftexture[stoi(p1[1])];
			}
		}
	}
	f.close();

	for (int i = 0; i < fcount; i++)
		for (int j = 0; j < 3; j++)
			color[i][j] = vec4(1, 1, 1, 1);

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) + sizeof(color) + sizeof(texture), NULL, GL_STATIC_DRAW);
	GLintptr offset = 0;
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vertex), vertex);
	offset += sizeof(vertex);
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(color), color);
	offset += sizeof(color);
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(texture), texture);
}

void BUILDING::load()
{
	b0.load();
	b1.load();
	b2.load();
	b3.load();
	apt.load();
}

void CAR::load()
{
	bus.load();
	car.load();
	rcar.load();
	taxi.load();
}


void ROAD::init(GLuint program)
{
	road = vec3(-1, 0, 0);
	line = vec3(-0.05, 0, 0.001);

	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	vTexture = glGetAttribLocation(program, "vTexture");
	glEnableVertexAttribArray(vTexture);
}

void FIELD::init(GLuint program)
{
	field[0] = vec3(-1.5, 0, 0);
	field[1] = vec3(1, 0, 0);

	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	vTexture = glGetAttribLocation(program, "vTexture");
	glEnableVertexAttribArray(vTexture);
}

void GRASS::init(GLuint program)
{
	grass[0] = vec3(-3.5, 0, 0);
	grass[1] = vec3(1.5, 0, 0);

	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	vTexture = glGetAttribLocation(program, "vTexture");
	glEnableVertexAttribArray(vTexture);
}

void TREE::init(GLuint program)
{
	tree[0][0] = vec3(-2, 0.5, 0);
	tree[1][0] = vec3(1.5, 0.5, 0);
	for (int i = 0; i < 2; i++)
		for (int j = 1; j < 20; j++)
			tree[i][j] = tree[i][j - 1] + vec3(0, 0.5, 0);
	
	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	vTexture = glGetAttribLocation(program, "vTexture");
	glEnableVertexAttribArray(vTexture);

	mat4 origin = Translate(160.519653, 155.436432, 161.745789);
	mat4 s = Scale(0.0014989181004011, 0.0024768708656754, 0.00148);
	mat4 r = RotateX(90);
	rest = r*s*origin;
}

void BUILDING::init(GLuint program)
{
	b0.init(program);
	b1.init(program);
	b2.init(program);
	b3.init(program);
	apt.init(program);
}

void CAR::init(GLuint program)
{
	bus.init(program);
	car.init(program);
	rcar.init(program);
	taxi.init(program);
}


void ROAD::draw(GLint pro, GLint model)
{
	tex.bind();
	mat4 n = Translate(-1 + road.x, -1 + road.y, road.z);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sizeof(vertex)));
	glVertexAttribPointer(vTexture, 2, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sizeof(vertex) + sizeof(color)));
	glUniformMatrix4fv(model, 1, GL_TRUE, n);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	ltex.bind();
	n = Translate(-1 + line.x, -1 + line.y, line.z);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sizeof(lvertex)));
	glVertexAttribPointer(vTexture, 2, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sizeof(lvertex) + sizeof(color)));
	glUniformMatrix4fv(model, 1, GL_TRUE, n);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void FIELD::draw(GLint pro, GLint model)
{
	for (int i = 0; i < 2; i++)
	{
		tex.bind();
		mat4 n = Translate(-1 + field[i].x, -1 + field[i].y, field[i].z);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0,
			BUFFER_OFFSET(0));
		glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0,
			BUFFER_OFFSET(sizeof(vertex)));
		glVertexAttribPointer(vTexture, 2, GL_FLOAT, GL_FALSE, 0,
			BUFFER_OFFSET(sizeof(vertex) + sizeof(color)));
		glUniformMatrix4fv(model, 1, GL_TRUE, n);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}

void GRASS::draw(GLint pro, GLint model)
{
	for (int i = 0; i < 2; i++)
	{
		tex.bind();
		mat4 n = Translate(-1 + grass[i].x, -1 + grass[i].y, grass[i].z);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0,
			BUFFER_OFFSET(0));
		glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0,
			BUFFER_OFFSET(sizeof(vertex)));
		glVertexAttribPointer(vTexture, 2, GL_FLOAT, GL_FALSE, 0,
			BUFFER_OFFSET(sizeof(vertex) + sizeof(color)));
		glUniformMatrix4fv(model, 1, GL_TRUE, n);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}

void TREE::draw(GLint pro, GLint model)
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 20; j++)
		{
			tex.bind();
			mat4 n = Translate(-1 + tree[i][j].x, -1 + tree[i][j].y, tree[i][j].z)*rest;
			glBindBuffer(GL_ARRAY_BUFFER, buffer);
			glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0,
				BUFFER_OFFSET(0));
			glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0,
				BUFFER_OFFSET(sizeof(vertex)));
			glVertexAttribPointer(vTexture, 2, GL_FLOAT, GL_FALSE, 0,
				BUFFER_OFFSET(sizeof(vertex) + sizeof(color)));
			glUniformMatrix4fv(model, 1, GL_TRUE, n);
			glDrawArrays(GL_TRIANGLES, 0, fcount * 3);
		}
}

void BUILDING::draw(GLint pro, GLint model)
{
	b0.draw(pro, model);
	b1.draw(pro, model);
	b2.draw(pro, model);
	b3.draw(pro, model);
	apt.draw(pro, model);
}

void CAR::draw(GLint pro, GLint model)
{
	bus.draw(pro, model);
	car.draw(pro, model);
	rcar.draw(pro, model);
	taxi.draw(pro, model);
}


void CAR::move()
{
	bus.move();
	car.move();
	rcar.move();
	taxi.move();
}