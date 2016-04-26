#version 430
layout(triangles) in;
layout(triangle_strip, max_vertices = 6) out;

in vec2 geom_uv[];
in vec3 geom_normal[];
in vec3 geom_worldpos[];
in vec3 geom_ViewPos[];

out vec2 frag_uv;
out vec3 frag_normal;
out vec3 frag_worldpos;
out vec3 frag_ViewPos;

void main()
{
	vec3 vt = normalize(geom_ViewPos[0] - geom_worldpos[0]);

	if(dot(vt, geom_normal[0]) >= -0.3)
	{
		for(int i = 0; i < 3; i++)
		{
			gl_Position = gl_in[i].gl_Position;
			frag_uv = geom_uv[i];
			frag_normal = geom_normal[i];
			frag_worldpos = geom_worldpos[i];
			frag_ViewPos = geom_ViewPos[i];
			EmitVertex();
		}
		EndPrimitive();
	}
}