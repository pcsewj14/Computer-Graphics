#include "Game.h"

int mode;

Texture chicken;
Texture no;
vec3 tvchic[524][3];
vec2 ttex[524][3];
vec3 ntex[524][3];
vec4 tcolor[524][3];
vec3 tangent[524][3];
vec3 bitangent[524][3];
GLuint chicB;
GLuint normalmap;
vec3 loc;
GLuint vPosition;
GLuint vColor;
GLuint vtexture;
GLuint vNormal;
GLuint vtan;
GLuint vbitan;
GLuint vEye;
mat4 rest;

GLuint program;

void GAME::load()
{
	map.load();

	no.load("nChic.png");
	chicken.load("Chicken.png");

	int vcount = 1; int tcount = 1; int ncount = 1;
	int fcount_ = 0;
	vec2 texture[195];
	vec3 chic[260];
	vec3 normal[395];

	ifstream f("Chicken.obj");

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
			chic[vcount++] = vec3(stof(t[1]), stof(t[2]), stof(t[3]));
		else if (flag.compare("vt") == 0)
			texture[tcount++] = vec2(stof(t[1]), 1 - stof(t[2]));
		else if (flag.compare("vn") == 0)
			normal[ncount++] = vec3(stof(t[1]), stof(t[2]), stof(t[3]));
		else if (flag.compare("f") == 0)
		{
			vector<string> p1 = tokenize(t[1], "/");
			vector<string> p2 = tokenize(t[2], "/");
			vector<string> p3 = tokenize(t[3], "/");

			tvchic[fcount_][0] = chic[stoi(p1[0])];
			tvchic[fcount_][1] = chic[stoi(p2[0])];
			tvchic[fcount_][2] = chic[stoi(p3[0])];

			ttex[fcount_][0] = texture[stoi(p1[1])];
			ttex[fcount_][1] = texture[stoi(p2[1])];
			ttex[fcount_][2] = texture[stoi(p3[1])];

			ntex[fcount_][0] = normal[stoi(p1[2])];
			ntex[fcount_][1] = normal[stoi(p2[2])];
			ntex[fcount_][2] = normal[stoi(p3[2])];

			vec3 pos1 = tvchic[fcount_][1] - tvchic[fcount_][0];
			vec3 pos2 = tvchic[fcount_][2] - tvchic[fcount_][0];

			vec2 uv1 = ttex[fcount_][1] - ttex[fcount_][0];
			vec2 uv2 = ttex[fcount_][2] - ttex[fcount_][0];

			float r = 1.0f / (uv1.x*uv2.y - uv1.y*uv2.x);

			tangent[fcount_][0] = (pos1*uv2.y - pos2*uv1.y)*r;
			bitangent[fcount_][0] = (pos2*uv1.x - pos1*uv2.x)*r;
			tangent[fcount_][1] = tangent[fcount_][0]; tangent[fcount_][2] = tangent[fcount_][0];
			bitangent[fcount_][1] = bitangent[fcount_][0]; bitangent[fcount_][2] = bitangent[fcount_][0];
			fcount_++;
		}
	}
	f.close();

	for (int i = 0; i < 524; i++)
		for (int j = 0; j < 3; j++)
			tcolor[i][j] = vec4(1, 1, 1, 1);

	glGenBuffers(1, &chicB);
	glBindBuffer(GL_ARRAY_BUFFER, chicB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tvchic) + sizeof(tcolor) + sizeof(ttex) + sizeof(ntex) + sizeof(tangent) + sizeof(bitangent), NULL, GL_STATIC_DRAW);
	GLintptr offset = 0;
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(tvchic), tvchic);
	offset += sizeof(tvchic);
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(tcolor), tcolor);
	offset += sizeof(tcolor);
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(ttex), ttex);
	offset += sizeof(ttex);
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(ntex), ntex);
	offset += sizeof(ntex);
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(tangent), tangent);
	offset += sizeof(tangent);
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(bitangent), bitangent);
}

void GAME::init()
{
	camera = 0; mode = 1;
	direc = 0;

	loc = vec3(1, 1, 0);
	
	glewExperimental = GL_TRUE;
	glewInit();

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	program = InitShader("vshader.glsl", "fshader.glsl");
	glUseProgram(program);
	pro = glGetUniformLocation(program, "projection");
	model = glGetUniformLocation(program, "model_view");

	glUniform1i(glGetUniformLocation(program, "texture"), 0);
	
	map.init(program);
	player.init(program);	//character init
	
	player.buffer();	//character buffer

	mat4 ori = Translate(6.25, 0, 10.1904);		//원점으로 옮겨서
	mat4 s = Scale(0.016, 0.016, 0.016);		//격자에 맞춤	원래크기 : x(1.08) y(1.08) z(1.8)
	mat4 r = RotateX(90);					//z가 위로가도록.
	rest = r*s*ori;
	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	vtexture = glGetAttribLocation(program, "vTexCoord");
	glEnableVertexAttribArray(vtexture);
	vNormal = glGetAttribLocation(program, "vNormal");
	glEnableVertexAttribArray(vNormal);
	vtan = glGetAttribLocation(program, "tangent");
	glEnableVertexAttribArray(vtan);
	vbitan = glGetAttribLocation(program, "bitangent");
	glEnableVertexAttribArray(vbitan);

	diffuse = glGetUniformLocation(program, "texture");
	normalmap = glGetUniformLocation(program, "tnormal");
	vEye = glGetAttribLocation(program, "vEye");

	glClearColor(1, 1, 1, 1);
}

void GAME::draw()
{
	glActiveTexture(GL_TEXTURE0);
	glLineWidth(2.0);
	mat4 m;
	if (mode == 1)
	{
		m = Ortho2D(-1.0 + camera, 1.0 + camera, -1.0, 1.0);
		glUniform3fv(vEye, 0, vec3(-1.0 + camera, 1.0 + camera, -1.0));
	}
	else if (mode == 2)
	{
		if (direc == 0)
		{
			vec4 eye = vec4(player.pos_x - 0.8, player.pos_y - 1, 1.25, 0.0);
			vec4 at = vec4(player.pos_x + 10, player.pos_y - 1, 0.0, 0.0);
			vec4 up = vec4(0.0, 0.0, 1.0, 0.0);
			m = Perspective(20, 1, 0.01, 5.0)*LookAt(eye, at, up);	
			glUniform3fv(vEye, 0, vec3(player.pos_x - 0.8, player.pos_y - 1, 1.25));
		}
		else if (direc == 1)
		{
			vec4 eye = vec4(player.pos_x - 1.0, player.pos_y + 0.8, 1.25, 0.0);
			vec4 at = vec4(player.pos_x - 1.0, player.pos_y - 10, 0.0, 0.0);
			vec4 up = vec4(0.0, 0.0, 1.0, 0.0);
			m = Perspective(20, 1, 0.01, 5.0)*LookAt(eye, at, up);
			glUniform3fv(vEye, 0, vec3(player.pos_x - 1.0, player.pos_y + 0.8, 1.25));
		}
		else
		{
			vec4 eye = vec4(player.pos_x + 1.0, player.pos_y - 0.8, 1.25, 0.0);
			vec4 at = vec4(player.pos_x + 1.0, player.pos_y + 10, 0.0, 0.0);
			vec4 up = vec4(0.0, 0.0, 1.0, 0.0);
			m = Perspective(20, 1, 0.01, 5.0)*LookAt(eye, at, up);
			glUniform3fv(vEye, 0, vec3(player.pos_x + 1.0, player.pos_y - 0.8, 1.25));
		}
	}
	else if (mode == 3)
	{
		if (direc == 0)//방향키에 따른 방향
		{
			vec4 eye = vec4(player.pos_x + 0.3, player.pos_y - 1, 1.1, 0.0);	//-1을 안해주면 matrix ㅜ을 적용안한 상태로 나오는거같아서 1을 빼줬는데
			vec4 at = vec4(player.pos_x + 10, player.pos_y - 1, -1.7, 0.0);					//문제는 얘가 어디를 보고있는건지도 잘 모르겠어...
			vec4 up = vec4(0.0, 0.0, 1.0, 0.0);//z축 방향으로 서있음
			m = Perspective(90, 1, 0.01, 5.0)*LookAt(eye, at, up);	
			glUniform3fv(vEye, 0, vec3(player.pos_x + 0.3, player.pos_y - 1, 1.1));
		}
		else if (direc == 1)
		{
			vec4 eye = vec4(player.pos_x - 1.0, player.pos_y - 0.3, 1.1, 0.0);
			vec4 at = vec4(player.pos_x - 1.0, player.pos_y - 10, -1.7, 0.0);
			vec4 up = vec4(0.0, 0.0, 1.0, 0.0);
			m = Perspective(90, 1, 0.01, 5.0)*LookAt(eye, at, up);
			glUniform3fv(vEye, 0, vec3(player.pos_x - 1.0, player.pos_y - 0.3, 1.1));
		}
		else
		{
			vec4 eye = vec4(player.pos_x + 1.0, player.pos_y + 0.3, 1.1, 0.0);
			vec4 at = vec4(player.pos_x + 1.0, player.pos_y + 10, -1.7, 0.0);
			vec4 up = vec4(0.0, 0.0, 1.0, 0.0);
			m = Perspective(90, 1, 0.01, 5.0)*LookAt(eye, at, up);
			glUniform3fv(vEye, 0, vec3(player.pos_x + 1.0, player.pos_y + 0.3, 1.1));
		}
	}
	mat4 n = Translate(-1.0, -1.0, 0.0);
	glUniformMatrix4fv(pro, 1, GL_TRUE, m);
	glUniformMatrix4fv(model, 1, GL_TRUE, n);

	map.draw(pro, model);
	player.draw(pro, model);	//character draw

	glActiveTexture(GL_TEXTURE0);
	chicken.bind();
	glUniform1i(diffuse, 0);
	glActiveTexture(GL_TEXTURE1);
	no.bind();
	glUniform1i(normalmap, 1);
	n = Translate(-1.0 + loc.x, -1.0 + loc.y, 0.0)*rest;
	glUniformMatrix4fv(model, 1, GL_TRUE, n);
	glBindBuffer(GL_ARRAY_BUFFER, chicB);
	GLintptr offset = 0;
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(offset)); offset += sizeof(tvchic);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(offset)); offset += sizeof(tcolor);
	glVertexAttribPointer(vtexture, 2, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(offset)); offset += sizeof(ttex);
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(offset)); offset += sizeof(ntex);
	glVertexAttribPointer(vtan, 3, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(offset)); offset += sizeof(tangent);
	glVertexAttribPointer(vbitan, 3, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(offset));
	glDrawArrays(GL_TRIANGLES, 0, 524*3);
	
	glutSwapBuffers();
}

bool GAME::finished()
{
	if (player.theta[RightUpperArm] != 180)
		return false;

	int i = (int)((player.pos_x + 0.9) * 10 + 0.5) / 2;
	float playery = player.pos_y + 1;
	float playerw = TORSO_WIDTH * 0.5 + UPPER_ARM_WIDTH;
	
	if (i >= MAP_SIZE) return true;
	
	for (int j = 0; j < CAR_N; j++)
	{
		float cary = map.road.car.car[i][j].y + map.road.car.cmove[i][j] - 0.2;
		float cwidth = map.road.car.width;

		if ((cary < playery + playerw) && (playery - playerw < cary + cwidth) && cary != 0)
			return true;
	}

	if (-camera > player.pos_x + 1.1)
		return true;

	if (playery >= 2.08 || playery <= -0.12)
		return true;

	return false;
}

bool GAME::treehere()
{
	int i = (int)((player.pos_x + 0.9) * 10 + 0.5) / 2;
	int j = (int)((player.pos_y + 1) / 0.222 + 0.5);

	if (map.field.tree.tree[i][j].x == 0)
		return false;
	else
		return true;
}

void GAME::move()
{
	camera = player.pos_x + 0.9;

	map.move();
	if (finished()) exit(0);

	glutPostRedisplay();
}

void GAME::keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case '1':
		mode = 1;
		break;
	case '2':
		mode = 2;
		break;
	case '3':
		mode = 3;
		break;
	case 'q':
		map.road.car.mo = 1;
		map.field.tree.mo = 1;	//wire frame
		glClearColor(1, 1, 1, 1);
		glUniform1i(glGetUniformLocation(program, "mo"), map.road.car.mo);
		break;
	case 'w':
		map.road.car.mo = 2;
		map.field.tree.mo = 2;
		glClearColor(0.2, 0.8, 1.0, 0.0);
		glUniform1i(glGetUniformLocation(program, "mo"), map.road.car.mo);
		break;
	case 'e':
		map.road.car.mo = 3;
		map.field.tree.mo = 3;
		glClearColor(0.2, 0.8, 1.0, 0.0);
		glUniform1i(glGetUniformLocation(program, "mo"), map.road.car.mo);
		break;
	case 'r':
		map.road.car.mo = 4;
		map.field.tree.mo = 4;
		glClearColor(0.2, 0.8, 1.0, 0.0);
		glActiveTexture(GL_TEXTURE1);
		no.bind();
		glUniform1i(normalmap, 1);
		glUniform1i(glGetUniformLocation(program, "mo"), map.road.car.mo);
		break;
	case 'o':
		map.road.car.light_position.w = 1.0;
		glUniform4fv(glGetUniformLocation(program, "LightPosition"),
			1, map.road.car.light_position);
		break;
	case 'p':
		map.road.car.light_position.w = 0.0;
		glUniform4fv(glGetUniformLocation(program, "LightPosition"),
			1, map.road.car.light_position);
		break;
	}
	glutPostRedisplay();
}