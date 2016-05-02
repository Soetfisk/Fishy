#version 430


out vec4 color;

uniform sampler2D particle_tex;
in vec2 Vertex_UV;

void main(){
	vec3 t = texture2D(particle_tex, Vertex_UV).rgb;
	color  = vec4(t, 1);

}