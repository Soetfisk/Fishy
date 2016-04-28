//////#version 430

in vec2 frag_uv;
in vec3 frag_normal;
in vec3 frag_worldpos;
in vec3 frag_ViewPos;

layout(location = 0)out vec3 color;
layout(location = 1)out vec3 color2;
layout(location = 2)out vec3 color3;
layout(location = 3)out vec3 color4;

uniform sampler2D diffuseTexture;

void main()
{
	vec3 lightPos = vec3(1,200000,3);
	vec3 V = normalize(frag_ViewPos - frag_worldpos); // pos to camera
	vec3 L = normalize(lightPos - frag_worldpos); // pos to light
	

	float dist = gl_FragCoord.z / gl_FragCoord.w; // distance

	color4 = vec3(dist,0,0);

	vec3 tempColor  = vec3(texture2D(diffuseTexture, frag_uv));

	color = tempColor;
	//color = vec3(0.5,0.5,0.5);

	color2 = frag_worldpos;
	color3 = frag_normal;
}