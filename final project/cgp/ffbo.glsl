#version 150
in vec2 TexCoords;
out vec4 color;

uniform sampler2D screenTexture;
uniform vec2 upleft;
uniform vec2 dright;
uniform float time;
uniform vec3 shockParams;

uniform int mode;

const float PI = 3.1415926535;
const float DIV = 50.0;

vec2 distort(vec2 v)
{
	float theta = atan(v.y, v.x);
	float radius = sqrt(v.x * v.x + v.y * v.y);
	radius = pow(radius, 2);
	v.x = radius * cos(theta);
	v.y = radius * sin(theta);
	return 0.5 * (v+1.0);
}

void main()
{ 
	if (mode == 0) color = texture(screenTexture, TexCoords);
	
	else if (mode == 1)
	{
		color = texture(screenTexture, TexCoords);		
		if ((gl_FragCoord.x > upleft.x && gl_FragCoord.x < dright.x)
			&& (500-gl_FragCoord.y > upleft.y && 500-gl_FragCoord.y < dright.y))
		{
			float sum = color.x + color.y + color.z;
			float ave = sum / 3;
			color = vec4(ave, ave, ave, 1);
		}
	}	//Èæ¹é

	else if (mode == 2)
	{
		color = texture(screenTexture, TexCoords);
		if ((gl_FragCoord.x > upleft.x && gl_FragCoord.x < dright.x)
			&& (500-gl_FragCoord.y > upleft.y && 500-gl_FragCoord.y < dright.y))
		{
			float r = 1 - color.x;
			float g = 1 - color.y;
			float b = 1 - color.z;
			color = vec4(r, g, b, 1);
		}
	}	//¹ÝÀü

	else if (mode == 3)
	{
		color = texture(screenTexture, TexCoords);
		if ((gl_FragCoord.x > upleft.x && gl_FragCoord.x < dright.x)
			&& (500-gl_FragCoord.y > upleft.y && 500-gl_FragCoord.y < dright.y))
		{
			int ix = int(TexCoords.x * 100);
			int iy = int(TexCoords.y * 100);
			float x = float(ix) / 100;
			float y = float(iy) / 100;
		    color = texture(screenTexture, vec2(x, y));
		}
	}	//¸ðÀÚÀÌÅ©

	else if (mode == 4)
	{
		color = texture(screenTexture, TexCoords);
		if ((gl_FragCoord.x > upleft.x && gl_FragCoord.x < dright.x)
			&& (500-gl_FragCoord.y > upleft.y && 500-gl_FragCoord.y < dright.y))
		{
			float weight[13]= {
			0.0561, 0.1353, 0.278, 0.4868, 0.7261, 0.9231,
			1, 0.9231, 0.7261, 0.4868, 0.278, 0.1353, 0.0561};
		
			float total = 6.2108;

			float blurw = 1.0 / 800.0;
			float blurh = 1.0 / 600.0;
			vec4 colorx = vec4(0, 0, 0, 0);
			vec4 colory = vec4(0, 0, 0, 0);
			for(int i = -6; i <= 6; i++)
			{
				colorx += weight[6+i] * texture(screenTexture, vec2(TexCoords.x + i*blurw, TexCoords.y));
				colory += weight[6+i] * texture(screenTexture, vec2(TexCoords.x, TexCoords.y + i*blurh));
			}
			colorx /= total;
			colory /= total;
			color = (colorx + colory) / 2;
		}
	}	//ºí·¯

	else if (mode == 5)
	{
		color = texture(screenTexture, vec2(TexCoords.x, TexCoords.y));
		if ((gl_FragCoord.x > upleft.x && gl_FragCoord.x < dright.x)
			&& (500-gl_FragCoord.y > upleft.y && 500-gl_FragCoord.y < dright.y))
		{
			float fx = float(int(color.x * 10)) / 10.0;
			float fy = float(int(color.y * 10)) / 10.0;
			float fz = float(int(color.z * 10)) / 10.0;
			vec4 toon = vec4(fx, fy, fz, 1.0);

			float sobelw = 1.0/700.0;
			float sobelh = 1.0/500.0;
	
			vec4 lt, t, rt, l, m, r, lb, b, rb;
			lt = texture(screenTexture, vec2(TexCoords.x - sobelw, TexCoords.y + sobelh));
			t = texture(screenTexture, vec2(TexCoords.x, TexCoords.y + sobelh));
			rt = texture(screenTexture, vec2(TexCoords.x + sobelw, TexCoords.y + sobelh));
			l = texture(screenTexture, vec2(TexCoords.x - sobelw, TexCoords.y));
			r = texture(screenTexture, vec2(TexCoords.x + sobelw, TexCoords.y));
			lb = texture(screenTexture, vec2(TexCoords.x - sobelw, TexCoords.y - sobelh));
			b = texture(screenTexture, vec2(TexCoords.x, TexCoords.y - sobelh));
			rb = texture(screenTexture, vec2(TexCoords.x + sobelw, TexCoords.y - sobelh));
	
			vec4 gx =  lt + 2*l + lb - rt - 2*r - rb;
			vec4 gy = -lt - 2*t - rt + lb + 2*b + rb;
			color = sqrt(gx*gx + gy*gy);
			if(color.x + color.y + color.z <= 1.5)
				color = toon;
			else
				color = vec4(0.0, 0.0, 0.0, 1.0);
		}
	}	//Ä«Å÷

	else if (mode == 6)
	{
		vec2 uv;
		vec2 dleft = vec2(upleft.x / 700.0,  (500.0 - dright.y)/500.0);
		vec2 upright = vec2(dright.x / 700.0, (500.0 - upleft.y)/500.0);
		float width = upright.x - dleft.x;
		float height = upright.y - dleft.y;
		vec2 xy = vec2((TexCoords.x - dleft.x)/width, (TexCoords.y - dleft.y)/height);
		xy = 2.0 * xy - 1.0;
		float dist = sqrt(xy.x * xy.x + xy.y * xy.y);
	
		if (xy.x >= -1 && xy.x <= 1 && xy.y >= -1 && xy.y <= 1)
		{
			if(dist < 1.0)
			{
				uv = distort(xy);
				uv.x = uv.x * width + dleft.x;
				uv.y = uv.y * height + dleft.y;
			}
			else
				uv = TexCoords;
		}
		else uv = TexCoords;

		color = texture2D(screenTexture, uv);
	}	//¾î¾È·»Áî

	else if (mode == 7)
	{
		vec2 center = vec2(upleft.x/700.0, (500.0 - upleft.y)/500.0);
		vec2 uv = TexCoords.xy;
		vec2 texCoord = uv;
		float distance = distance(uv, center);
		if( (distance <= (time + shockParams.z)) && 
			(distance >= (time - shockParams.z)) )
		{
			float diff = (distance - time);
			float powDiff = 1.0 - pow(abs(diff*shockParams.x), shockParams.y);
			float diffTime = diff*powDiff;
			vec2 diffUV = normalize(uv - center);
			texCoord = uv + (diffUV * diffTime);
		}
		color = texture(screenTexture, texCoord);
	}	//shake

	else if (mode == 8)
	{
		vec2 uv;
		if ((gl_FragCoord.x > upleft.x && gl_FragCoord.x < dright.x)
			&& (500-gl_FragCoord.y > upleft.y && 500-gl_FragCoord.y < dright.y))
		{
			int ix = int(TexCoords.x * DIV);
			int iy = int(TexCoords.y * DIV);
			float x = float(ix) / DIV;
			float y = float(iy) / DIV;
			vec2 xy = vec2(TexCoords.x - x - (1/DIV), TexCoords.y-y-(1/DIV));
			xy = 2* DIV * xy - 1.0;
			float dist = sqrt(xy.x * xy.x + xy.y * xy.y);

			uv = distort(xy) / (2 * DIV);
			uv.x += x+0.025;
			uv.y += y+0.025;
		}
		else uv = TexCoords;

		color = texture(screenTexture, uv);
	}
}