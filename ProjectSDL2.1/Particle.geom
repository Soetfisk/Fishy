#version 430

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform float particelSize;

void main(){
	
	vec4 position = gl_in[0].gl_Position;
	mat4 ProjectionViewMatrix = ProjectionMatrix * ViewMatrix;

	vec2 dLeft = position.xy + (vec2(-.5, -.5) );
	gl_Position = ProjectionViewMatrix * vec4(dLeft, position.zw);
	EmitVertex();

	vec2 dRight = position.xy + (vec2(.5, -.5) );
	gl_Position = ProjectionViewMatrix * vec4(dRight, position.zw);
	EmitVertex();

	vec2 uLeft = position.xy + (vec2(-.5, .5) );
	gl_Position = ProjectionViewMatrix * vec4(uLeft, position.zw);
	EmitVertex();

	vec2 uRight = position.xy + (vec2(.5, .5) );
	gl_Position = ProjectionViewMatrix * vec4(uRight, position.zw);
	EmitVertex();

	EndPrimitive();
}

//#version 430

//layout (points) in;
//layout (triangle_strip, max_vertices = 4) out;
//uniform mat4 ProjectionMatrix;
//uniform mat4 ViewMatrix;
//uniform float particelSize;

//void main(){
	
//	vec4 viewPosition =ViewMatrix* gl_in[0].gl_Position;




//	vec2 dLeft = position.xy + (vec2(-.5, -.5));
//	gl_Position = ProjectionMatrix * vec4(dLeft, position.zw);
	
//	EmitVertex();

//	vec2 dRight = position.xy + (vec2(.5, -.5) );
//	gl_Position = ProjectionMatrix * vec4(dRight, position.zw);
//	EmitVertex();

//	vec2 uLeft = position.xy + (vec2(-.5, .5) );
//	gl_Position = ProjectionMatrix * vec4(uLeft, position.zw);
//	EmitVertex();

//	vec2 uRight = position.xy + (vec2(.5, .5) );
//	gl_Position = ProjectionMatrix * vec4(uRight, position.zw);
//	EmitVertex();

//	EndPrimitive();
//}