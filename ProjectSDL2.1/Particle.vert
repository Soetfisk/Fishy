#version 430

layout (location = 0) in vec4 pos;

uniform mat4 TransformMatrix;
uniform mat4 ProjectionViewMatrix;
uniform mat4 ViewPos;



void main(){
	
	gl_Position = ProjectionViewMatrix * ViewPos * pos;
}