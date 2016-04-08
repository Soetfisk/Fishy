#version 450

in VS
{
	//vec3 pos
	vec2 texCoord;
	vec3 normal;
} vertex;

uniform sampler2D diffuseTexture;
uniform vec3 material.ambient;
uniform vec3 material.diffuse;
uniform vec3 material.specular;
uniform float material.shininess;

int main()
{
	gl_Color = vec4(255, 0, 0, 1);
}