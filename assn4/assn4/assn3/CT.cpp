#include "CT.h"

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
	wcar.load("roadline.png");
	tcar.load("Taxi.png");
	no.load("nTaxi.png");

	int vcount = 1; int tcount = 1; int ncount = 1;
	int fcount = 0; int fcount_ = 0;
	int toggle = 0;
	vec2 texture[475];
	vec3 taxi[317];
	vec3 normal[475];

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
		else if (flag.compare("vt") == 0)
			texture[tcount++] = vec2(stof(t[1]), 1-stof(t[2]));
		else if (flag.compare("vn")==0)
			normal[ncount++] = vec3(stof(t[1]), stof(t[2]), stof(t[3]));
		else if (flag.compare("f") == 0)
		{
			vector<string> p1 = tokenize(t[1], "/");
			vector<string> p2 = tokenize(t[2], "/");
			vector<string> p3 = tokenize(t[3], "/");

			tvcar[fcount_][0] = taxi[stoi(p1[0])];
			tvcar[fcount_][1] = taxi[stoi(p2[0])];
			tvcar[fcount_][2] = taxi[stoi(p3[0])];

			ttex[fcount_][0] = texture[stoi(p1[1])];
			ttex[fcount_][1] = texture[stoi(p2[1])];
			ttex[fcount_][2] = texture[stoi(p3[1])];

			wvcar[fcount_][0] = taxi[stoi(p1[0])];
			wvcar[fcount_][1] = taxi[stoi(p2[0])];
			wvcar[fcount_][2] = taxi[stoi(p3[0])];
			
			wtex[fcount_][0] = vec2(0,0);
			wtex[fcount_][1] = vec2(0,1);
			wtex[fcount_][2] = vec2(1,0);

			ntex[fcount_][0] = normal[stoi(p1[1])];
			ntex[fcount_][1] = normal[stoi(p2[1])];
			ntex[fcount_][2] = normal[stoi(p3[1])];

			vec3 pos1 = tvcar[fcount_][1] - tvcar[fcount_][0];
			vec3 pos2 = tvcar[fcount_][2] - tvcar[fcount_][0];

			vec2 uv1 = ttex[fcount_][1] - ttex[fcount_][0];
			vec2 uv2 = ttex[fcount_][2] - ttex[fcount_][0];

			float r = 1.0f / (uv1.x*uv2.y - uv1.y*uv2.x);

			tangent[fcount_][0] = (pos1*uv2.y - pos2*uv1.y)*r;
			bitangent[fcount_][0] = (pos2*uv1.x - pos1*uv2.x)*r;
			tangent[fcount_][1] = tangent[fcount_][0]; tangent[fcount_][2] = tangent[fcount_][0];
			bitangent[fcount_][1] = bitangent[fcount_][0]; bitangent[fcount_][2] = bitangent[fcount_][0];
			fcount_++;
			
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
			rigidcolor[i][j] = vec4(0, 0, 0, 1);

	for (int i = 0; i < 158; i++)
		for (int j = 0; j < 3; j++)
			tcolor[i][j] = vec4(1, 1, 1, 1);

	glGenBuffers(1, &carB[0]);
	glBindBuffer(GL_ARRAY_BUFFER, carB[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rigidcar) + sizeof(rigidcolor), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(rigidcar), rigidcar);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(rigidcar), sizeof(rigidcolor), rigidcolor);

	glGenBuffers(1, &carB[2]);
	glBindBuffer(GL_ARRAY_BUFFER, carB[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(wvcar) + sizeof(tcolor) + sizeof(wtex), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(wvcar), wvcar);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(wvcar), sizeof(tcolor), tcolor);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(wvcar) + sizeof(tcolor), sizeof(wtex), wtex);

	glGenBuffers(1, &carB[1]);
	glBindBuffer(GL_ARRAY_BUFFER, carB[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tvcar) + sizeof(tcolor) + sizeof(ttex) + sizeof(ntex) + sizeof(tangent) + sizeof(bitangent), NULL, GL_STATIC_DRAW);
	GLintptr offset = 0;
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(tvcar), tvcar);
	offset += sizeof(tvcar);
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

void CAR::init(int* map, GLuint program)
{
	mo = 1;
	width = 0.2;
	shininess = 100.0;

	light_position = vec4(-1.0, 0.0, 1.0, 0.0);
	light_ambient = vec4(0.3, 0.3, 0.3, 1.0);
	light_diffuse = vec4(1.0, 1.0, 1.0, 1.0);
	light_specular = vec4(1.0, 1.0, 1.0, 1.0);

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
			vtexture[i][j] = glGetAttribLocation(program, "vTexCoord");
			glEnableVertexAttribArray(vtexture[i][j]);
			vNormal[i][j] = glGetAttribLocation(program, "vNormal");
			glEnableVertexAttribArray(vNormal[i][j]);
			vtan[i][j] = glGetAttribLocation(program, "tangent");
			glEnableVertexAttribArray(vtan[i][j]);
			vbitan[i][j] = glGetAttribLocation(program, "bitangent");
			glEnableVertexAttribArray(vbitan[i][j]);
		}
	diffuse = glGetUniformLocation(program, "texture");
	normalmap = glGetUniformLocation(program, "tnormal");
	glUniform4fv(glGetUniformLocation(program, "AmbientProduct"),
		1, light_ambient);
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"),
		1, light_diffuse);
	glUniform4fv(glGetUniformLocation(program, "SpecularProduct"),
		1, light_specular);
	glUniform4fv(glGetUniformLocation(program, "LightPosition"),
		1, light_position);

	glUniform1f(glGetUniformLocation(program, "Shininess"),
		shininess);
}

void CAR::draw(int* map, GLint pro, GLint model)
{
	if (mo == 1)
	{
		wcar.bind();
		for (int i = 0; i < MAP_SIZE; i++)
			if (map[i] == _road)
			{
				for (int j = 0; j < CAR_N; j++)
				{
					mat4 n = Translate(-1.0 + car[i][j].x, -1.0 + car[i][j].y + cmove[i][j], car[i][j].z)*rest;
					glUniformMatrix4fv(model, 1, GL_TRUE, n);

					glBindBuffer(GL_ARRAY_BUFFER, carB[2]);
					glVertexAttribPointer(vPosition[i][j], 3, GL_FLOAT, GL_FALSE, 0,
						BUFFER_OFFSET(0));
					glVertexAttribPointer(vColor[i][j], 4, GL_FLOAT, GL_FALSE, 0,
						BUFFER_OFFSET(sizeof(wvcar)));
					glVertexAttribPointer(vtexture[i][j], 2, GL_FLOAT, GL_FALSE, 0,
						BUFFER_OFFSET(sizeof(wvcar) + sizeof(tcolor)));
					glDrawArrays(GL_TRIANGLES, 0, 158 * 3);

					glBindBuffer(GL_ARRAY_BUFFER, carB[0]);
					glVertexAttribPointer(vPosition[i][j], 3, GL_FLOAT, GL_FALSE, 0,
						BUFFER_OFFSET(0));
					glVertexAttribPointer(vColor[i][j], 4, GL_FLOAT, GL_FALSE, 0,
						BUFFER_OFFSET(sizeof(rigidcar)));
					glDrawArrays(GL_LINES, 0, 632);
				}
			}
	}
	else
	{
		glActiveTexture(GL_TEXTURE0);
		tcar.bind();
		glUniform1i(diffuse, 0);
		glActiveTexture(GL_TEXTURE1);
		no.bind();
		glUniform1i(normalmap, 1);
		for (int i = 0; i < MAP_SIZE; i++)
			if (map[i] == _road)
			{
				for (int j = 0; j < CAR_N; j++)
				{
					mat4 n = Translate(-1.0 + car[i][j].x, -1.0 + car[i][j].y + cmove[i][j], car[i][j].z)*rest;
					glBindBuffer(GL_ARRAY_BUFFER, carB[1]);
					GLintptr offset = 0;
					glVertexAttribPointer(vPosition[i][j], 3, GL_FLOAT, GL_FALSE, 0,
						BUFFER_OFFSET(offset)); offset += sizeof(tvcar);
					glVertexAttribPointer(vColor[i][j], 4, GL_FLOAT, GL_FALSE, 0,
						BUFFER_OFFSET(offset)); offset += sizeof(tcolor);
					glVertexAttribPointer(vtexture[i][j], 2, GL_FLOAT, GL_FALSE, 0,
						BUFFER_OFFSET(offset)); offset += sizeof(ttex);
					glVertexAttribPointer(vNormal[i][j], 3, GL_FLOAT, GL_FALSE, 0,
						BUFFER_OFFSET(offset)); offset += sizeof(ntex);
					glVertexAttribPointer(vtan[i][j], 3, GL_FLOAT, GL_FALSE, 0,
						BUFFER_OFFSET(offset)); offset += sizeof(tangent);
					glVertexAttribPointer(vbitan[i][j], 3, GL_FLOAT, GL_FALSE, 0,
						BUFFER_OFFSET(offset));
					glUniformMatrix4fv(model, 1, GL_TRUE, n);
					glDrawArrays(GL_TRIANGLES, 0, 158*3);
				}
			}
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

void TREE::load()
{
	no.load("nTree.png");
	wtree.load("roadline.png");
	ttree.load("christmas_tree.png");
	int vcount = 1; int tcount = 1;
	int ncount = 1;
	int fcount = 0; int fcount_ = 0;
	int toggle = 0;
	vec3 ctree[633];
	vec3 normal[949];
	vec2 texture[949];
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
		else if (flag.compare("vt") == 0)
			texture[tcount++] = vec2(stof(t[1]), 1 - stof(t[2]));
		else if (flag.compare("vn") == 0)
			normal[ncount++] = vec3(stof(t[1]), stof(t[2]), stof(t[3]));
		else if (flag.compare("f") == 0)
		{
			vector<string> p1 = tokenize(t[1], "/");
			vector<string> p2 = tokenize(t[2], "/");
			vector<string> p3 = tokenize(t[3], "/");

			tvtree[fcount_][0] = ctree[stoi(p1[0])];
			tvtree[fcount_][1] = ctree[stoi(p2[0])];
			tvtree[fcount_][2] = ctree[stoi(p3[0])];

			ttex[fcount_][0] = texture[stoi(p1[1])];
			ttex[fcount_][1] = texture[stoi(p2[1])];
			ttex[fcount_][2] = texture[stoi(p3[1])];

			wvtree[fcount_][0] = ctree[stoi(p1[0])];
			wvtree[fcount_][1] = ctree[stoi(p2[0])];
			wvtree[fcount_][2] = ctree[stoi(p3[0])];

			wtex[fcount_][0] = vec2(0, 0);
			wtex[fcount_][1] = vec2(0, 1);
			wtex[fcount_][2] = vec2(1, 0);

			ntex[fcount_][0] = normal[stoi(p1[1])];
			ntex[fcount_][1] = normal[stoi(p2[1])];
			ntex[fcount_][2] = normal[stoi(p3[1])];

			vec3 pos1 = tvtree[fcount_][1] - tvtree[fcount_][0];
			vec3 pos2 = tvtree[fcount_][2] - tvtree[fcount_][0];

			vec2 uv1 = ttex[fcount_][1] - ttex[fcount_][0];
			vec2 uv2 = ttex[fcount_][2] - ttex[fcount_][0];

			float r = 1.0f / (uv1.x*uv2.y - uv1.y*uv2.x);

			tangent[fcount_][0] = (pos1*uv2.y - pos2*uv1.y)*r;
			bitangent[fcount_][0] = (pos2*uv1.x - pos1*uv2.x)*r;
			tangent[fcount_][1] = tangent[fcount_][0]; tangent[fcount_][2] = tangent[fcount_][0];
			bitangent[fcount_][1] = bitangent[fcount_][0]; bitangent[fcount_][2] = bitangent[fcount_][0];
			fcount_++;

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
			rigidcolor[i][j] = vec4(0, 0, 0, 1.0);

	for (int i = 0; i < 316; i++)
		for (int j = 0; j < 3; j++)
			tcolor[i][j] = vec4(1, 1, 1, 1);

	glGenBuffers(1, &treeB[0]);
	glBindBuffer(GL_ARRAY_BUFFER, treeB[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rigidtree) + sizeof(rigidcolor), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(rigidtree), rigidtree);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(rigidtree), sizeof(rigidcolor), rigidcolor);

	glGenBuffers(1, &treeB[2]);
	glBindBuffer(GL_ARRAY_BUFFER, treeB[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(wvtree) + sizeof(tcolor) + sizeof(wtex), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(wvtree), wvtree);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(wvtree), sizeof(tcolor), tcolor);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(wvtree) + sizeof(tcolor), sizeof(wtex), wtex);

	glGenBuffers(1, &treeB[1]);
	glBindBuffer(GL_ARRAY_BUFFER, treeB[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tvtree) + sizeof(tcolor) + sizeof(ttex) + sizeof(ntex) + sizeof(tangent) + sizeof(bitangent), NULL, GL_STATIC_DRAW);
	GLintptr offset = 0;
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(tvtree), tvtree);
	offset += sizeof(tvtree);
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

void TREE::init(int* map, GLuint program)
{
	mo = 1;

	light_position = vec4(1.0, 1.0, 1.0, 0.0);
	light_ambient = vec4(0.3, 0.3, 0.3, 1.0);
	light_diffuse = vec4(1.0, 1.0, 1.0, 1.0);
	light_specular = vec4(1.0, 1.0, 1.0, 1.0);

	shininess = 100.0;

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

	/*glUniform4fv(glGetUniformLocation(program, "AmbientProduct"),
		1, light_ambient);
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"),
		1, light_diffuse);
	glUniform4fv(glGetUniformLocation(program, "SpecularProduct"),
		1, light_specular);
	glUniform4fv(glGetUniformLocation(program, "LightPosition"),
		1, light_position);

	glUniform1f(glGetUniformLocation(program, "Shininess"),
		shininess);*/

}

void TREE::draw(int* map, GLint pro, GLint model)
{
	if (mo == 1)
	{
		wtree.bind();
		for (int i = 1; i < MAP_SIZE; i++)
			if (map[i] == _field)
			{
				for (int j = 0; j < 10; j++)
				{
					mat4 n = Translate(-1.0 + tree[i][j].x, -1.0 + tree[i][j].y, tree[i][j].z)*rest;
					glUniformMatrix4fv(model, 1, GL_TRUE, n);

					glBindBuffer(GL_ARRAY_BUFFER, treeB[2]);
					glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0,
						BUFFER_OFFSET(0));
					glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0,
						BUFFER_OFFSET(sizeof(wvtree)));
					glVertexAttribPointer(vtexture, 2, GL_FLOAT, GL_FALSE, 0,
						BUFFER_OFFSET(sizeof(wvtree) + sizeof(tcolor)));
					glDrawArrays(GL_TRIANGLES, 0, 316 * 3);

					glBindBuffer(GL_ARRAY_BUFFER, treeB[0]);
					glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0,
						BUFFER_OFFSET(0));
					glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0,
						BUFFER_OFFSET(sizeof(rigidtree)));
					glDrawArrays(GL_LINES, 0, 1264);
				}
			}
	}
	else
	{
		glActiveTexture(GL_TEXTURE0);
		ttree.bind();
		glUniform1i(diffuse, 0);
		glActiveTexture(GL_TEXTURE1);
		no.bind();
		glUniform1i(normalmap, 1);
		for (int i = 1; i < MAP_SIZE; i++)
			if (map[i] == _field)
			{
				for (int j = 0; j < 10; j++)
				{
					mat4 n = Translate(-1.0 + tree[i][j].x, -1.0 + tree[i][j].y, tree[i][j].z)*rest;
					glBindBuffer(GL_ARRAY_BUFFER, treeB[1]);
					GLintptr offset = 0;
					glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0,
						BUFFER_OFFSET(offset)); offset += sizeof(tvtree);
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
					glUniformMatrix4fv(model, 1, GL_TRUE, n);
					glDrawArrays(GL_TRIANGLES, 0, 316*3);
				}
			}
	}
}