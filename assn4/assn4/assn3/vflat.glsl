#version 150

in vec4 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;

out vec3 frag;
out vec2 texCoord;

uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
uniform mat4 model_view;
uniform mat4 projection;
uniform vec4 LightPosition;
uniform float Shininess;

void main()
{
    gl_Position = projection*model_view*vPosition;
	texCoord = vTexCoord;
	frag = (model_view*vPosition).xyz;
}