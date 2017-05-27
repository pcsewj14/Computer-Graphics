#include "car.h"

void BUS::load()
{
	tex.load("bus.png");
	int vcount = 1; int tcount = 1; fcount = 0;

	vec2 ftexture[593];
	vec3 fvertex[449];

	ifstream f("bus.obj");

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

void SCAR::load()
{
	tex.load("car.png");
	int vcount = 1; int tcount = 1; fcount = 0;

	vec2 ftexture[516];
	vec3 fvertex[313];

	ifstream f("car.obj");

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

void RCAR::load()
{
	tex.load("rcar.png");
	int vcount = 1; int tcount = 1; fcount = 0;

	vec2 ftexture[516];
	vec3 fvertex[313];

	ifstream f("car.obj");

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

void TAXI::load()
{
	tex.load("taxi.png");
	int vcount = 1; int tcount = 1; fcount = 0;

	vec2 ftexture[684];
	vec3 fvertex[433];

	ifstream f("taxi.obj");

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


void BUS::init(GLuint program)
{
	m[0] = 0; m[1] = 0;

	obj[0] = vec3(-0.7, 6, 0); obj[1] = vec3(0.7, 6, 0);

	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	vTexture = glGetAttribLocation(program, "vTexture");
	glEnableVertexAttribArray(vTexture);

	mat4 origin = Translate(76.690109, 76.161728, 169.549362);
	mat4 s = Scale(0.0025898142231082, 0.0029135410009967, 0.0029135410009967);
	mat4 r = RotateX(90);
	rest[0] = r*s*origin;
	rest[1] = RotateZ(180)*rest[0];
}

void SCAR::init(GLuint program)
{
	m[0] = 0; m[1] = 0;

	obj[0] = vec3(-0.7, 9, 0); obj[1] = vec3(0.7, 9, 0);

	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	vTexture = glGetAttribLocation(program, "vTexture");
	glEnableVertexAttribArray(vTexture);

	mat4 origin = Translate(52.057175, 51.222984, 111.284286);
	mat4 s = Scale(0.0036935579787307, 0.0036935579787307, 0.0036935579787307);
	mat4 r = RotateX(90);
	rest[0] = r*s*origin;
	rest[1] = RotateZ(180)*rest[0];
}

void RCAR::init(GLuint program)
{
	m[0] = 0; m[1] = 0;

	obj[0] = vec3(-0.7, 3, 0); obj[1] = vec3(0.7, 3, 0);

	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	vTexture = glGetAttribLocation(program, "vTexture");
	glEnableVertexAttribArray(vTexture);

	mat4 origin = Translate(52.057175, 51.222984, 111.284286);
	mat4 s = Scale(0.0036935579787307, 0.0036935579787307, 0.0036935579787307);
	mat4 r = RotateX(90);
	rest[0] = r*s*origin;
	rest[1] = RotateZ(180)*rest[0];
}

void TAXI::init(GLuint program)
{
	m[0] = 0; m[1] = 0;

	obj[0] = vec3(-0.7, 12, 0); obj[1] = vec3(0.7, 12, 0);

	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	vTexture = glGetAttribLocation(program, "vTexture");
	glEnableVertexAttribArray(vTexture);

	mat4 origin = Translate(52.050011, 52.139084, 111.111099);
	mat4 s = Scale(0.0036936613566868, 0.0036936613566868, 0.0036936613566868);
	mat4 r = RotateX(90);
	rest[0] = r*s*origin;
	rest[1] = RotateZ(180)*rest[0];
}


void BUS::draw(GLint pro, GLint model)
{
	for (int i = 0; i < 2; i++)
	{
		tex.bind();
		mat4 n = Translate(-1 + obj[i].x, -1 + obj[i].y + m[i], obj[i].z)*rest[i];
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

void SCAR::draw(GLint pro, GLint model)
{ 
	for (int i = 0; i < 2; i++)
	{
		tex.bind();
		mat4 n = Translate(-1 + obj[i].x, -1 + obj[i].y + m[i], obj[i].z)*rest[i];
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

void RCAR::draw(GLint pro, GLint model)
{
	for (int i = 0; i < 2; i++)
	{
		tex.bind();
		mat4 n = Translate(-1 + obj[i].x, -1 + obj[i].y + m[i], obj[i].z)*rest[i];
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

void TAXI::draw(GLint pro, GLint model)
{
	for (int i = 0; i < 2; i++)
	{
		tex.bind();
		mat4 n = Translate(-1 + obj[i].x, -1 + obj[i].y + m[i], obj[i].z)*rest[i];
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


void BUS::move()
{
	m[0] -= 0.005;
	m[1] += 0.005;
	if (obj[0].y + m[0] < 0)
		m[0] = 6;
	if (obj[1].y + m[1] > 12)
		m[1] = -6;
}

void SCAR::move()
{
	m[0] -= 0.005;
	m[1] += 0.005;
	if (obj[0].y + m[0] < 0)
		m[0] = 3;
	if (obj[1].y + m[1] > 12)
		m[1] = -9;
}

void RCAR::move()
{
	m[0] -= 0.005;
	m[1] += 0.005;
	if (obj[0].y + m[0] < 0)
		m[0] = 9;
	if (obj[1].y + m[1] > 12)
		m[1] = -3;
}

void TAXI::move()
{
	m[0] -= 0.005;
	m[1] += 0.005;
	if (obj[0].y + m[0] < 0)
		m[0] = 0;
	if (obj[1].y + m[1] > 12)
		m[1] = -12;
}