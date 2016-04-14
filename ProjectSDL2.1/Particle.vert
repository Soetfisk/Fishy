#version 430


uniform mat4 TransformMatrix;
uniform mat4 ProjectionViewMatrix;
uniform mat4 ViewPos;

in vec4 pos;

void main(){
	gl_Position = pos;
}