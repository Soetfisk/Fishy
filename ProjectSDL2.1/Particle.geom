#version 430

const vec2 corners[4] = { 
    vec2(0.0, 0.0), vec2(0.0, 1.0), vec2(1.0, 0.0), vec2(1.0, 1.0) };

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;

in float v_scale[];

out vec2 Vertex_UV;
out vec3 geom_pos;


void main(){
	
	int derp = 13;


	for(int i = 0; i<4;i++){
		vec4 eyePos  =ViewMatrix *  gl_in[0].gl_Position ;
		eyePos.xy += (corners[i] - vec2(.5)) *v_scale[0];
		geom_pos = gl_in[0].gl_Position.xyz;
		gl_Position = ProjectionMatrix * eyePos;
		Vertex_UV = corners[i];

		//gl_Position = ProjectionMatrix* v_transMatrix[0] * eyePos;
		EmitVertex();
	}

	EndPrimitive();

	
}