#version 430

in vec2 frag_uv;

out vec3 color;

uniform sampler2D texture;
uniform sampler2D texture2;
uniform sampler2D texture3;

void main()
{


	//color  = vec3(1, 1, 0);
	color = vec3(texture2D(texture, frag_uv)) + vec3(texture2D(texture2, frag_uv)) + vec3(texture2D(texture3, frag_uv));
}