#version 430

const vec2 corners[4] = { 
    vec2(0.0, 0.0), vec2(0.0, 1.0), vec2(1.0, 0.0), vec2(1.0, 1.0) };

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;

in mat4 v_transMatrix[];

out vec2 Vertex_UV;


void main(){
	
	for(int i = 0; i<4;i++){
		vec4 eyePos  =ViewMatrix *  gl_in[0].gl_Position ;
		eyePos.xy += corners[i] - vec2(.5);
		gl_Position = ProjectionMatrix * eyePos;
		Vertex_UV = corners[i];
		//gl_Position = ProjectionMatrix* v_transMatrix[0] * eyePos;
		EmitVertex();
	}

	//vec4 position = gl_in[0].gl_Position;
	//mat4 ProjectionViewMatrix = ProjectionMatrix * ViewMatrix;

	//vec2 dLeft = position.xy + (vec2(-.5, -.5) );
	//gl_Position = ProjectionViewMatrix * vec4(dLeft, position.zw);
	//EmitVertex();

	//vec2 dRight = position.xy + (vec2(.5, -.5) );
	//gl_Position = ProjectionViewMatrix * vec4(dRight, position.zw);
	//EmitVertex();

	//vec2 uLeft = position.xy + (vec2(-.5, .5) );
	//gl_Position = ProjectionViewMatrix * vec4(uLeft, position.zw);
	//EmitVertex();

	//vec2 uRight = position.xy + (vec2(.5, .5) );
	//gl_Position = ProjectionViewMatrix * vec4(uRight, position.zw);
	//EmitVertex();

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