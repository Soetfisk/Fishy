#version 430


out vec4 color;

uniform sampler2D particle_tex;
in vec2 Vertex_UV;

void main(){
	vec4 tempColor = texture2D(particle_tex, Vertex_UV).rgba;
	
	if(tempColor.a<.5f)
		discard;
	
	color  = vec4(texture2D(particle_tex, Vertex_UV).rgba);

}