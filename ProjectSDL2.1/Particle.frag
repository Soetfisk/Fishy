#version 430

layout(location = 0)out vec4 color;
layout(location = 1)out vec4 color2;
layout(location = 2)out vec4 color3;
layout(location = 3)out vec4 color4;
layout(location = 4)out vec4 color5;
layout(location = 5)out vec4 color6;

//out vec4 color;

uniform sampler2D particle_tex;
in vec2 Vertex_UV;
in vec3 geom_pos;

void main(){
	vec4 tempColor = texture2D(particle_tex, -Vertex_UV).rgba;
	
	if(tempColor.a<.5f)
		discard;
	
	float dist = gl_FragCoord.z / gl_FragCoord.w; // distance

	color4 = vec4(dist,0,0,1);

	color = tempColor;

	color2 = vec4(geom_pos, 1);
	color3 = vec4(0,1,0,1);
	color5 = vec4((tempColor.rgb)/5, 1);
	color6 = vec4(0,0,0, 0);

}