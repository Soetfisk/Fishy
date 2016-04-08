#version 450

layout(location = 0) in position;
layout(location = 1) in texCoord;
layout(location = 2) in normal

out VS
{
	//vec3 pos
	vec2 texCoord;
	vec3 normal;
} vertex

uniform mat4 TransformMatrix;
uniform mat4 ProjectionViewMatrix;
uniform mat4 ViewPos

int main()
{
	gl_Position = ProjectionVeiwMatrix * TransformMatrix * vec4(position, 1);
	vertex.texCoord = texCoord;
	vertex.normal = normal;
}