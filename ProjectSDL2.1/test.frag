//////#version 430

in vec2 frag_uv;
in vec3 frag_normal;
in vec3 frag_worldpos;
in vec3 frag_ViewPos;

layout(location = 0)out vec3 color;
layout(location = 1)out vec3 color2;
layout(location = 2)out vec3 color3;

uniform sampler2D diffuseTexture;

const vec3 fogColor = vec3(0.0,0.0,1);

void main()
{
	vec3 lightPos = vec3(1,2,3);
	vec3 V = normalize(frag_ViewPos - frag_worldpos); // pos to camera
	vec3 L = normalize(lightPos - frag_worldpos); // pos to light
	

	float dist = gl_FragCoord.z / gl_FragCoord.w; // distance
	float fogFactor = 0;

	fogFactor = (80-dist) / (80 - 2);
	fogFactor = clamp(fogFactor,0.0,1.0);

	float angle = max(dot(L, frag_normal), 0.0);
	vec3 tempColor  = clamp(angle * vec3(1, 0, 0) + vec3(0.01,0.01,0.01),0.0,1.0);

	color = clamp(mix(fogColor, tempColor, fogFactor),0.0,1.0);
	//color = vec3(0.5,0.5,0.5);

	color2 = vec3(dist,dist,dist);
	color3 = vec3(0, 0, 1);
}