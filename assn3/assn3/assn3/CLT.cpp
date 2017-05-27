#include "CLT.h"

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

void CAR::load()
{
	int vcount = 1; int fcount = 0; int toggle = 0;
	vec3 taxi[317];
	ifstream f("Taxi.obj");

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
			taxi[vcount++] = vec3(stof(t[1]), stof(t[2]), stof(t[3]));
		else if (flag.compare("f") == 0)
		{
			vector<string> p1 = tokenize(t[1], "/");
			vector<string> p2 = tokenize(t[2], "/");
			vector<string> p3 = tokenize(t[3], "/");
			
			if (toggle == 0)
			{
				rigidcar[fcount][0] = taxi[stoi(p1[0])];
				rigidcar[fcount][1] = taxi[stoi(p2[0])];
				rigidcar[fcount][2] = taxi[stoi(p2[0])];
				rigidcar[fcount][3] = taxi[stoi(p3[0])];
				toggle = 1;
			}
			else
			{
				rigidcar[fcount][4] = taxi[stoi(p2[0])];
				rigidcar[fcount][5] = taxi[stoi(p3[0])];
				rigidcar[fcount][6] = taxi[stoi(p3[0])];
				rigidcar[fcount++][7] = taxi[stoi(p1[0])];
				toggle = 0;
			}
		}
	}
	f.close();

	for (int i = 0; i < 79; i++)
		for (int j = 0; j < 8; j++)
			rigidcolor[i][j] = vec4(1, 0, 0, 1);

	glGenBuffers(1, &carB);
	glBindBuffer(GL_ARRAY_BUFFER, carB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rigidcar) + sizeof(rigidcolor), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(rigidcar), rigidcar);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(rigidcar), sizeof(rigidcolor), rigidcolor);	
}

void CAR::init(int* map, GLuint program)
{
	width = 0.2;
	vec3 car_hw[2] = { vec3(0.16,0.0,0.0), vec3(0.0,0.2,0.0) };

	for (int i = 0; i < MAP_SIZE; i++)
	{
		if (map[i] == _road)
		{
			space[i] = rand() % 3 * 0.2 + 0.6;
			speed[i] = rand() % 5 * 0.0001 + 0.0006;
			direc[i] = rand() % 2 - 0.5;
			for (int j = 0; j < CAR_N; j++)
				cmove[i][j] = 0;
		}
	}

	for (int i = 0; i < MAP_SIZE; i++)
	{
		if (map[i] == _road)
		{
			for (int j = 0; j < CAR_N; j++)
			{
				car[i][j] = vec3(0.2*i + 0.02, 2 - j*(space[i] + 0.2), 0.0);
			}
		}
	}

	mat4 ori = Translate(0.54, 0, 0.9);		//원점으로 옮겨서
	mat4 s = Scale(0.148, 0.185, 0.1);		//격자에 맞춤	원래크기 : x(1.08) y(1.08) z(1.8)
	mat4 r = RotateX(90);					//z가 위로가도록.
	rest = r*s*ori;

	for (int i = 0; i < MAP_SIZE; i++)
		for (int j = 0; j < CAR_N; j++)
		{
			vPosition[i][j] = glGetAttribLocation(program, "vPosition");
			glEnableVertexAttribArray(vPosition[i][j]);
			vColor[i][j] = glGetAttribLocation(program, "vColor");
			glEnableVertexAttribArray(vColor[i][j]);
		}
}

void CAR::draw(GLint pro, GLint model)
{
	for (int i = 0; i < MAP_SIZE;i++)
		for (int j = 0; j < CAR_N; j++)
		{
			mat4 n = Translate(-1.0 + car[i][j].x, -1.0 + car[i][j].y + cmove[i][j], car[i][j].z)*rest;
			glBindBuffer(GL_ARRAY_BUFFER, carB);
			glVertexAttribPointer(vPosition[i][j], 3, GL_FLOAT, GL_FALSE, 0,
				BUFFER_OFFSET(0));
			glVertexAttribPointer(vColor[i][j], 4, GL_FLOAT, GL_FALSE, 0,
				BUFFER_OFFSET(sizeof(rigidcar)));
			glUniformMatrix4fv(model, 1, GL_TRUE, n);
			glDrawArrays(GL_LINES, 0, 632);
		}
}

void CAR::reInit()
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		float com = (CAR_N - 1)*0.2 + CAR_N*space[i];
		if (direc[i] > 0)
		{
			for (int j = 0; j < CAR_N; j++)
				if (cmove[i][j] - j*(space[i] + 0.2) >= com - 2)
					cmove[i][j] = j*(space[i] + 0.2) - 2.2;
		}
		else
		{
			float com = 2 - CAR_N * (0.2 + space[i]);
			for (int j = 0; j < CAR_N; j++)
				if (cmove[i][j] - j*(space[i] + 0.2) <= com - 2)
					cmove[i][j] = j*(space[i] + 0.2) + 0.2;
		}
	}
}

void CAR::move()
{
	for (int i = 0; i < MAP_SIZE;i++)
		for (int j = 0; j < CAR_N; j++)
			cmove[i][j] += speed[i]*direc[i];
	reInit();
}

void LOG::init(int num, GLuint program, float di)
{
	vec3 h = vec3(0.16, 0.0, 0.0);
	space = rand() % 3 * 0.222 + 0.666;
	speed = rand() % 5 * 0.00015 + 0.0006;
	direc = di;
	width = rand() % 3 * 0.222 + 0.666;
	for (int i = 0; i < LOG_N; i++)
		lmove[i] = 0;

	for (int i = 0; i < LOG_N; i++)
	{
		log[i][0] = vec3(0.2*num + 0.02, 2 - i*(space + width), 0.0);
		log[i][1] = log[i][0] + vec3(0.0, width, 0.0);
		log[i][2] = log[i][0] + h;
		log[i][3] = log[i][1]; log[i][4] = log[i][2];
		log[i][5] = log[i][3] + h;
	}
	for (int i = 0; i < LOG_N; i++)
		for (int j = 0; j < 6; j++)
			log_color[i][j] = vec4(0.4, 0.2, 0.1, 1.0);

	for (int i = 0; i < LOG_N; i++)
	{
		vPosition[i] = glGetAttribLocation(program, "vPosition");
		glEnableVertexAttribArray(vPosition[i]);
		vColor[i] = glGetAttribLocation(program, "vColor");
		glEnableVertexAttribArray(vColor[i]);
	}
}

void LOG::buffer()
{
	for (int i = 0; i < LOG_N; i++)
	{
		glGenBuffers(1, &logB[i]);
		glBindBuffer(GL_ARRAY_BUFFER, logB[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(log[i]) + sizeof(log_color[i]), NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(log[i]), log[i]);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(log[i]), sizeof(log_color[i]), log_color[i]);
	}
}

void LOG::draw(GLint pro, GLint model)
{
	for (int i = 0; i < LOG_N; i++)
	{
		mat4 n = Translate(-1.0, -1.0 + lmove[i], 0.0);
		glBindBuffer(GL_ARRAY_BUFFER, logB[i]);
		glVertexAttribPointer(vPosition[i], 3, GL_FLOAT, GL_FALSE, 0,
			BUFFER_OFFSET(0));
		glVertexAttribPointer(vColor[i], 4, GL_FLOAT, GL_FALSE, 0,
			BUFFER_OFFSET(sizeof(log[i])));
		glUniformMatrix4fv(model, 1, GL_TRUE, n);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}

void LOG::reInit()
{
	if (direc > 0)
	{
		float com = (LOG_N - 1)*width + LOG_N*space;
		for (int i = 0; i < LOG_N; i++)
			if (lmove[i] - i*(space + width) >= com - 2)
				lmove[i] = i*(space + width) - (2 + width);
	}
	else
	{
		float com = 2 - LOG_N * (width + space);
		for (int i = 0; i < LOG_N; i++)
			if (lmove[i] - i*(space + width) <= com - 2)
				lmove[i] = i*(space + width);
	}
}

void LOG::move()
{
	for (int i = 0; i < LOG_N; i++)
		lmove[i] += speed*direc;
	reInit();
}

void TREE::load()
{
	int vcount = 1; int fcount = 0; int toggle = 0;
	vec3 ctree[633];
	ifstream f("christmas_tree.obj");

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
			ctree[vcount++] = vec3(stof(t[1]), stof(t[2]), stof(t[3]));
		else if (flag.compare("f") == 0)
		{
			vector<string> p1 = tokenize(t[1], "/");
			vector<string> p2 = tokenize(t[2], "/");
			vector<string> p3 = tokenize(t[3], "/");

			if (toggle == 0)
			{
				rigidtree[fcount][0] = ctree[stoi(p1[0])];
				rigidtree[fcount][1] = ctree[stoi(p2[0])];
				rigidtree[fcount][2] = ctree[stoi(p2[0])];
				rigidtree[fcount][3] = ctree[stoi(p3[0])];
				toggle = 1;
			}
			else
			{
				rigidtree[fcount][4] = ctree[stoi(p2[0])];
				rigidtree[fcount][5] = ctree[stoi(p3[0])];
				rigidtree[fcount][6] = ctree[stoi(p3[0])];
				rigidtree[fcount++][7] = ctree[stoi(p1[0])];
				toggle = 0;
			}
		}
	}
	f.close();

	for (int i = 0; i < 158; i++)
		for (int j = 0; j < 8; j++)
			rigidcolor[i][j] = vec4(0.5, 0.3, 0.2, 1.0);

	/*cout << rigidcar[78][0] << endl;
	cout << rigidcar[78][1] << endl;
	cout << rigidcar[78][2] << endl;
	cout << rigidcar[78][3] << endl;
	cout << rigidcar[78][4] << endl;
	cout << rigidcar[78][5] << endl;
	cout << rigidcar[78][6] << endl;
	cout << rigidcar[78][7] << endl;*/

	glGenBuffers(1, &treeB);
	glBindBuffer(GL_ARRAY_BUFFER, treeB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rigidtree) + sizeof(rigidcolor), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(rigidtree), rigidtree);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(rigidtree), sizeof(rigidcolor), rigidcolor);

}

void TREE::init(int* map, GLuint program)
{
	for (int i = 0; i < MAP_SIZE; i++)
		if (map[i] == _field)
		{
			for (int j = 0; j < 10; j++)
			{
				if (i == 0)
					tree[0][j] = vec3(0, 0, 0);
				else
				{
					int chance = rand() % 4;
					if (chance == 0)
						tree[i][j] = vec3(0.2*i + 0.02, j*0.222, 0.0);
					else
						tree[i][j] = vec3(0, 0, 0);
				}
			}
		}

	mat4 ori = Translate(0.4375, 0, 0.4375);	//원점으로 옮겨서
	mat4 s = Scale(0.182857, 0.1, 0.19);		//격자에 맞춤	원래길이 : x(0.875) y(1.875) z(0.875)
	mat4 r = RotateX(90);						//y가 위쪽을 보고있어서 눕혀줌
	rest = r*s*ori;
	
	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
}

void TREE::draw(GLint pro, GLint model)
{
	for (int i = 0; i < MAP_SIZE; i++)
		for (int j = 0; j < 10; j++)
		{
			mat4 n = Translate(-1.0 + tree[i][j].x, -1.0 + tree[i][j].y, tree[i][j].z)*rest;
			glBindBuffer(GL_ARRAY_BUFFER, treeB);
			glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0,
				BUFFER_OFFSET(0));
			glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0,
				BUFFER_OFFSET(sizeof(rigidtree)));
			glUniformMatrix4fv(model, 1, GL_TRUE, n);
			glDrawArrays(GL_LINES, 0, 1264);
		}
}