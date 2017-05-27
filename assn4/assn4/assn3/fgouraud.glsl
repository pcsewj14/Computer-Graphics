#version 150

in vec4 color;
in vec2 texCoord;

uniform sampler2D texture;

void
main()
{
    gl_FragColor = color * texture2D(texture, texCoord);
}