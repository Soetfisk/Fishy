#version 430

layout (location = 0) in vec4 pos;
layout (location = 1) in float scale;

uniform mat4 ViewPos;

out float v_scale;

void main(){
	v_scale = scale;
	gl_Position =  pos;//vec4(pos, 1);
	
	//gl_Position = ProjectionViewMatrix  * vec4(pos, 1);
	//gl_Position = pos;
}