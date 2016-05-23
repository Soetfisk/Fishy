#version 430

in vec2 frag_uv;
in vec3 frag_normal;
in vec3 frag_worldpos;
in vec3 frag_ViewPos;

layout(location = 0)out vec4 color;
layout(location = 1)out vec4 color2;
layout(location = 2)out vec4 color3;
layout(location = 3)out vec4 color4;
layout(location = 4)out vec4 color5;
layout(location = 5)out vec4 color6;

uniform sampler2D diffuseTexture;
uniform vec3 diffuse;
uniform vec3 ambient;
uniform vec3 specular;
uniform float shininess;

void main()
{
	vec3 lightPos = vec3(1,200000,3);
	vec3 V = normalize(frag_ViewPos - frag_worldpos); // pos to camera
	vec3 L = normalize(lightPos - frag_worldpos); // pos to light
	
	float dist = gl_FragCoord.z / gl_FragCoord.w; // distance

	color4 = vec4(dist,0,0,1);

	vec4 tempColor  = vec4(diffuse, 1) * texture2D(diffuseTexture, frag_uv);
	tempColor = vec4(1,0,0,1);

	color = tempColor;

	color2 = vec4(frag_worldpos, 1);
	color3 = vec4(frag_normal, 1);
	color5 = vec4(ambient, 1);
	color6 = vec4(specular, shininess);
}