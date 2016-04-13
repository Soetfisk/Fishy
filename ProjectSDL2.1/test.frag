#version 430

in vec2 vsTexCoord;
in vec3 vsNormal;
in vec3 vsPos;

out vec3 color;
out vec3 color2;
out vec3 color3;

uniform sampler2D diffuseTexture;

void main()
{
	
	vec3 lightPos = vec3(1,2,3);

	float angle = max(dot(normalize(lightPos-vsPos), vsNormal), 0.0);

	color  = angle * vec3(1, 0, 0);

	color2 = vec3(0,0,0.5);
	color3 = vec3(0,0.5,0);
}