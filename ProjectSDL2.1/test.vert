#version 430

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out vec2 geom_uv;
out vec3 geom_normal;
out vec3 geom_worldpos;
out vec3 geom_ViewPos;

uniform mat4 TransformMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform vec3 ViewPos;

void main()
{
 
	gl_Position = ProjectionMatrix * ViewMatrix * TransformMatrix * vec4(position, 1);
	geom_uv = texCoord;
	geom_normal = normalize(mat3(TransformMatrix) * normal);
	geom_worldpos = vec3(TransformMatrix * vec4(position, 1));
	geom_ViewPos = ViewPos;
}