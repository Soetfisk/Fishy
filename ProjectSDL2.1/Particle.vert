#version 430

layout (location = 0) in vec4 pos;

uniform mat4 ViewPos;



void main(){
	gl_Position =  pos;//vec4(pos, 1);
	//gl_Position = ProjectionViewMatrix  * vec4(pos, 1);
	//gl_Position = pos;
}