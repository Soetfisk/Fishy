#version 430


out vec4 color;

uniform sampler2D tex;
in vec2 Vertex_UV;

void main(){
	//vec3 t = texture(tex, Vertex_UV).rgb;
	color  = vec4(255,0,0, 255.0f);

}