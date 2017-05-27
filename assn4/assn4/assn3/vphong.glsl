#version 150

in vec4 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;

out vec3 fN;
out vec3 fE;
out vec3 fL;
out vec2 texCoord;

uniform mat4 model_view;
uniform mat4 projection;
uniform vec4 LightPosition;

void main()
{
	fN = vNormal;
	fE = vPosition.xyz;
	fL = LightPosition.xyz;

	if (LightPosition.w != 0.0) {
		fL = LightPosition.xyz - vPosition.xyz;
	}
	gl_Position = projection * model_view * vPosition;
	texCoord = vTexCoord;
}
