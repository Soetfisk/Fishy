#version 430

layout (location = 0) in vec4 pos;
layout (location = 1) in mat4 transformMatrix;

uniform mat4 ViewPos;

out mat4 v_transMatrix;

void main(){
	v_transMatrix = transformMatrix;
	gl_Position =  pos;//vec4(pos, 1);
	
	//gl_Position = ProjectionViewMatrix  * vec4(pos, 1);
	//gl_Position = pos;
}