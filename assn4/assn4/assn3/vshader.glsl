#version 150

in vec4 vPosition;
in vec3 vNormal;
in vec4 vColor;
in vec2 vTexCoord;
in vec3 tangent;
in vec3 bitangent;

out vec4 color;
out vec4 color1;
out vec3 frag;
out vec3 fN;
out vec3 fE;
out vec3 fL;
out vec2 texCoord;
out vec3 tan;
out vec3 bitan;
out vec3 n;
//out mat4 mv;

uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
uniform mat4 model_view;
uniform mat4 projection;
uniform vec4 LightPosition;
uniform float Shininess;
uniform vec3 vEye;
uniform sampler2D texture;
uniform sampler2D tnormal;
uniform int mo;

void
main()
{
	//mv = model_view;
	tan = tangent;
	bitan = bitangent;
	n = vNormal;
	
	if(mo == 1)
	{
		gl_Position = projection*model_view*vPosition;
		texCoord = vTexCoord;
		color = vColor;
	}

	else if(mo == 2)
	{
		gl_Position = projection*model_view*vPosition;
		texCoord = vTexCoord;
		frag = (model_view*vPosition).xyz;
		fN = frag;
		fL = LightPosition.xyz;
		color = vColor;
	}

	else if(mo == 3)
	{
		// Transform vertex  position into eye coordinates
		vec3 pos = (model_view * vPosition).xyz;
		texCoord = vTexCoord;
	
		vec3 L = normalize( LightPosition.xyz );
		vec3 E = normalize(- pos );
		vec3 H = normalize( L + E );

		if (LightPosition.w != 0.0) {
			L = normalize((LightPosition.xyz - pos));
		}

		vec3 M = normalize( model_view*vec4(vNormal, 0.0) ).xyz;

		// Compute terms in the illumination equation
		vec4 ambient = AmbientProduct;

		float Kd = max( dot(L, M), 0.0 );
		vec4  diffuse = Kd*DiffuseProduct;

		float Ks = pow( max(dot(M, H), 0.0), Shininess );
		vec4  specular = Ks * SpecularProduct;
    
		if( dot(L, M) < 0.0 ) {
			specular = vec4(0.0, 0.0, 0.0, 1.0);
		} 

		color = ambient + diffuse + specular;
		color.a = 1.0;

		gl_Position = projection*model_view*vPosition;
		color1= vColor;
	}

	else if(mo == 4)
	{
		fN = (model_view * vec4(vNormal, 0.0)).xyz;
		fE = vPosition.xyz;//-(model_view * vPosition).xyz;
		fL = LightPosition.xyz;

		if (LightPosition.w != 0.0) {
			fL = LightPosition.xyz - (model_view * vPosition).xyz;
		}

		gl_Position = projection*model_view * vPosition;
		texCoord = vTexCoord;
		color = vColor;
	}
}
