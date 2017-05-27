#version 150

in vec4 vPosition;
in vec4 vColor;
in vec2 vTexture;

out vec4 color;
out vec2 texCoord;

uniform mat4 model_view;
uniform mat4 projection;

void
main()
{
    gl_Position = projection*model_view*vPosition;
	color = vColor;
	texCoord = vTexture;
}
