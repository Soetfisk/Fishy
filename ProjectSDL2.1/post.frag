#version 430

in vec2 frag_uv;

out vec3 color;

uniform sampler2D texture;
uniform float offset;
#define T texture2D(texture,0.5+(p.xy*=.992))

void main()
{
	vec3 p = gl_FragCoord.xyz / vec3(1024/2,768,1) - 0.5;
	vec3 o = T.rbb;
	for (float i=0.;i<100.;i++) 
		p.z += pow(max(0.,.5-length(T.rg)),2.)*exp(-i*.08);

	//vec2 uv = frag_uv;
	//uv.x += (sin(uv.y * 4 * 2 * 3.1315 + offset) / 300);
	//color  = vec3(1, 1, 0);
	color = vec3(texture2D(texture, frag_uv) + vec3(0,0,0.1));
}