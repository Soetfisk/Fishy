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
uniform float offset;

void main()
{
	
	float dist = gl_FragCoord.z / gl_FragCoord.w; // distance

	color4 = vec4(dist,0,0,1);
	vec2 uv = frag_uv;

	uv.x += (sin(uv.x * 4 * 2 * 3.1315 + offset) / (300 * 0.1));
	uv.y += (sin(uv.y * 4 * 2 * 3.1315 + offset) / (300 * 0.1));

	vec4 tempColor  = vec4(diffuse, 1) * texture2D(diffuseTexture, uv);
	//tempColor = vec4(sin(offset),0,0,0);

	color = tempColor;

	color2 = vec4(vec3(0,0,0), 1);
	color3 = vec4(frag_normal, 1);
	color5 = vec4(vec3(0.4,0.4,0.4), 1);
	//color6 = vec4(specular, shininess);
}