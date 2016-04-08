#version 430

in vec2 vsTexCoord;
in vec3 vsNormal;
in vec3 vsPos;

//out vec4 color;

uniform sampler2D diffuseTexture;

void main()
{
	
	vec3 lightPos = vec3(3,3,3);

	float angle = max(dot(normalize(lightPos-vsPos), vsNormal), 0.0);

	gl_FragColor  = angle * vec4(1, 0, 0, 1);
}