#version 150

// per-fragment interpolated values from the vertex shader
in vec4 color;
in vec4 color1;
in vec3 frag;
in vec3 fN;
in vec3 fL;
in vec3 fE;
in vec2 texCoord;
in vec3 tan;
in vec3 bitan;
in vec3 n;
in mat3 mv;

uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
uniform mat4 model_view;
uniform vec4 LightPosition;
uniform float Shininess;
uniform sampler2D texture;
uniform sampler2D tnormal;
uniform int mo;

void main()
{
	mat3 normalMatrix = (mat3(model_view));
	vec3 T = normalize(normalMatrix * tan).xyz;
	vec3 B = normalize(normalMatrix * bitan).xyz;
	vec3 N = normalize(normalMatrix * n).xyz;

	mat3 TBN = (mat3(T, B, N));

	if(mo == 1)
	{
		gl_FragColor = color * texture2D(texture, texCoord);
	}

	else if(mo == 2)
	{
		vec3 X = dFdx(fN);
		vec3 Y = dFdy(fN);
		vec3 normal = normalize(cross(X, Y));
		vec3 mapping = normalize(texture2D(tnormal, texCoord).rgb * 2 - 1);
		//normal = TBN*mapping;

		vec3 lightdirection = normalize(fL);
		if (LightPosition.w != 0.0) {
			lightdirection = normalize(fL - frag);
		}

		float light = max(0.0, dot(lightdirection, normal));

		//gl_FragColor = vec4(normal, 1.0);
		gl_FragColor = color * vec4(light, light, light, 1.0) * texture2D(texture, texCoord);
	}

	else if(mo == 3)
	{
		gl_FragColor =  color1 * color * texture2D(texture, texCoord);
	}

	else if(mo == 4)
	{	
		// Normalize the input lighting vectors
		vec3 N = normalize(fN);
		vec3 E = normalize(fE);
		vec3 L = normalize(fL);
		vec3 H = normalize( L + E );

		vec3 normal = normalize(texture2D(tnormal, texCoord).rgb * 2 - vec3(1,1,1));
		vec3 WN = normalize(TBN*normal);// + 0.5*N);	//이걸 하면 평면

		vec4 ambient = AmbientProduct;
		float dotprod = dot(L, WN);
		//if (dotprod < 0) { WN = -WN; }
		float Kd = max(dot(L, WN), 0.0);
		vec4 diffuse = Kd*DiffuseProduct;
		float Ks = pow(max(dot(WN, H), 0.0), Shininess);
		vec4 specular = Ks*SpecularProduct;
		// discard the specular highlight if the light's behind the vertex
		//if( dot(L, WN) < 0.0 )
			//specular = vec4(0.0, 0.0, 0.0, 1.0);
		gl_FragColor = ambient + diffuse + specular;
		gl_FragColor.a = 1.0;
		gl_FragColor *= color * texture2D(texture, texCoord);
	}
}
