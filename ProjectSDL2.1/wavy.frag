#version 430

in vec2 frag_uv;

out vec3 color;

uniform sampler2D texture;
uniform float offset;
uniform float waveLength;

void main()
{

	vec2 uv = frag_uv;
	uv.x += (sin(uv.y * 4 * 2 * 3.1315 + offset) / (300 * waveLength));
	//color  = vec3(1, 1, 0);
	color = vec3(texture2D(texture, uv));
}