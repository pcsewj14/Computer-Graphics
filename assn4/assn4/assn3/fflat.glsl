#version 150

in vec4 color;
in vec2 texCoord;
in vec3 frag;

uniform vec4 LightPosition;
uniform sampler2D texture;

void main()
{
	vec3 X = dFdx(frag);
    vec3 Y = dFdy(frag);
	vec3 normal = normalize(cross(X, Y));

	vec3 lightDirection = normalize(LightPosition.xyz - frag);
    
    float light = max(0.0, dot(lightDirection, normal));

    gl_FragColor = vec4(normal, 1.0);
	gl_FragColor = vec4(light, light, light, 1.0) * texture2D(texture, texCoord);
}