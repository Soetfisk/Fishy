#version 430

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

out vec2 frag_uv;
out vec3 frag_normal;
out vec3 frag_worldpos;
out vec3 frag_ViewPos;

uniform mat4 TransformMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform vec3 ViewPos;

void main()
{
 
	gl_Position =  ProjectionMatrix * ViewMatrix * TransformMatrix * vec4(position, 1);
	frag_uv = texCoord;
	frag_normal = normalize(mat3(TransformMatrix) * normal);
	frag_worldpos = vec3(TransformMatrix * vec4(position, 1));
	frag_ViewPos = ViewPos;
}