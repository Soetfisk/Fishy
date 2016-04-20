#version 430

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out vec2 vsTexCoord;
out vec3 vsNormal;
out vec3 vsPos;
out vec3 vsViewPos;

uniform mat4 TransformMatrix;
uniform mat4 ProjectionViewMatrix;
uniform vec3 ViewPos;

void main()
{
 
	gl_Position = ProjectionViewMatrix * TransformMatrix * vec4(position, 1);
	vsTexCoord = texCoord;
	vsNormal = normalize(mat3(TransformMatrix) * normal);
	vsPos = vec3(TransformMatrix * vec4(position, 1));
	vsViewPos = ViewPos;
}