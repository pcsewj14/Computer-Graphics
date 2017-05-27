#include "building.h"

vector<string> tokenize(string str, string delim) {
	vector<string> v;
	size_t seek = 0;

	while (str.length() > seek) {
		size_t pos;
		pos = str.find_first_of(delim, seek);

		if (pos != string::npos) {
			v.push_back(str.substr(seek, pos - seek));
			seek = pos + 1;
		}
		else {
			v.push_back(str.substr(seek));
			seek = str.length();
		}
	}

	return v;
}

void B0::load()
{
	tex.load("building0.png");
	int vcount = 1; int tcount = 1; fcount = 0;

	vec3 fvertex[13];
	vec2 ftexture[33];

	ifstream f("building0.obj");

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

void B1::load()
{
	tex.load("building1.png");
	int vcount = 1; int tcount = 1; fcount = 0;

	vec3 fvertex[75];
	vec2 ftexture[143];

	ifstream f("building1.obj");

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

void B2::load()
{
	tex.load("building2.png");
	int vcount = 1; int tcount = 1; fcount = 0;

	vec3 fvertex[27];
	vec2 ftexture[67];

	ifstream f("building2.obj");

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

void B3::load()
{
	tex.load("building3.png");
	int vcount = 1; int tcount = 1; fcount = 0;

	vec3 fvertex[33];
	vec2 ftexture[97];

	ifstream f("building3.obj");

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

void APT::load()
{
	tex.load("apt.png");
	int vcount = 1; int tcount = 1; fcount = 0;

	vec3 fvertex[9];
	vec2 ftexture[25];

	ifstream f("apt.obj");

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


void B0::init(GLuint program)
{
	b0[0] = vec3(2.5, 2, 0);
	b0[1] = vec3(2.5, 4, 0);

	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	vTexture = glGetAttribLocation(program, "vTexture");
	glEnableVertexAttribArray(vTexture);

	mat4 origin = Translate(50, 57.207577, 50);
	mat4 s = Scale(0.02, 0.02, 0.02);
	mat4 r = RotateX(90);
	rest = r*s*origin;
}

void B1::init(GLuint program)
{
	b1 = vec3(2.5, 6, 0);

	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	vTexture = glGetAttribLocation(program, "vTexture");
	glEnableVertexAttribArray(vTexture);

	mat4 origin = Translate(121.594543, 100, 124.950485);
	mat4 s = Scale(0.0081649154521984, 0.0081649154521984, 0.0081649154521984);
	mat4 r = RotateX(90);
	rest = r*s*origin;
}

void B2::init(GLuint program)
{
	b2 = vec3(2.5, 8, 0);

	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	vTexture = glGetAttribLocation(program, "vTexture");
	glEnableVertexAttribArray(vTexture);

	mat4 origin = Translate(100, 100, 100);
	mat4 s = Scale(0.0101811948261326, 0.0101811948261326, 0.0101811948261326);
	mat4 r = RotateX(90);
	rest = r*s*origin;
}

void B3::init(GLuint program)
{
	b3 = vec3(4.5, 10, 0);

	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	vTexture = glGetAttribLocation(program, "vTexture");
	glEnableVertexAttribArray(vTexture);

	mat4 origin = Translate(99.709999, 84.623642, 99.178963);
	mat4 s = Scale(0.0099970528688143, 0.0099970528688143, 0.0099970528688143);
	mat4 r = RotateZ(-90)*RotateX(90);
	rest = r*s*origin;
}

void APT::init(GLuint program)
{
	apt[0] = vec3(-2, 1.5, 0);
	for (int i = 1; i < 4; i++)
		apt[i] = apt[i - 1] + vec3(0, 1.8, 0);

	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	vTexture = glGetAttribLocation(program, "vTexture");
	glEnableVertexAttribArray(vTexture);

	mat4 origin = Translate(44.671192, 59.491814, 27.070169);
	mat4 s = Scale(0.0184705163828124, 0.0184705163828124, 0.0184705163828124);
	mat4 r = RotateZ(180)*RotateX(90);
	rest = r*s*origin;
}


void B0::draw(GLint pro, GLint model)
{
	for (int i = 0; i < 2; i++)
		{
			tex.bind();
			mat4 n = Translate(-1 + b0[i].x, -1 + b0[i].y, b0[i].z) * rest;
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

void B1::draw(GLint pro, GLint model)
{
	tex.bind();
	mat4 n = Translate(-1 + b1.x, -1 + b1.y, b1.z) * rest;
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

void B2::draw(GLint pro, GLint model)
{
	tex.bind();
	mat4 n = Translate(-1 + b2.x, -1 + b2.y, b2.z) * rest;
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

void B3::draw(GLint pro, GLint model)
{
	tex.bind();
	mat4 n = Translate(-1 + b3.x, -1 + b3.y, b3.z) * rest;
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

void APT::draw(GLint pro, GLint model)
{
	for (int i = 0; i < 4; i++)
	{
		tex.bind();
		mat4 n = Translate(-1 + apt[i].x, -1 + apt[i].y, apt[i].z) * rest;
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