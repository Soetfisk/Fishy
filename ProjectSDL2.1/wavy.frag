#version 430

in vec2 frag_uv;

out vec3 color;

uniform sampler2D texture;
uniform float offset;
uniform float waveLength;

void main()
{

	vec2 uv = frag_uv;
	if((uv.x > 0.008 && uv.x < 0.992) && (uv.y > 0.008 && uv.y < 0.992) )
	{
		uv.x += (sin(uv.y * 4 * 2 * 3.1315 + offset) / (300 * waveLength));
	}
	
	//uv.y += (sin(uv.y * 4 * 2 * 3.1315 + offset) / (300 * waveLength));
	//uv.x += ((1 + 0.9*cos(8*offset))*(1 + 0.1*cos(24*offset)) * (0.9 + 0.05*cos(200*offset)) * (1 + sin(offset))) / 4;
	//color  = vec3(1, 1, 0);
	color = vec3(texture2D(texture, uv));
}