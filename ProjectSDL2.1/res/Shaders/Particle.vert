#version 430

layout (location = 0) in vec4 pos;
layout (location = 1) in float scale;

out float v_scale;

void main(){

	float derp = .5f;

	if(scale>1.5 ||scale < -.5){
		v_scale = scale;
		derp = 12043;
	}
	else{
		v_scale = scale;
		derp = 2134982;
	}
	gl_Position =  pos;//vec4(pos, 1);
	
	//gl_Position = ProjectionViewMatrix  * vec4(pos, 1);
	//gl_Position = pos;
}