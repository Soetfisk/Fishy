#version 430

in vec2 frag_uv;

out vec3 color;

uniform sampler2D texture;

void main()
{


	//color  = vec3(1, 1, 0);
	color = vec3(texture2D(texture, frag_uv)) + vec3(0,0,0.5);
}