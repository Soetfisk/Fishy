#version 430 compatibility

#extension GL_ARB_compute_shader : enable
#extension GL_ARB_shader_storage_buffer_object : enable

struct Particle{
	vec4 pos;
	float speed;
	mat4 transformMatrix;
};


layout( std140, binding=4 ) buffer Pos {
	vec4 Position[];
};

layout(std140, binding = 5) buffer Vel{
	vec4 Velocities[];
};

layout(std140, binding = 6) buffer Col{
	vec4 Colors[];
};

layout(local_size_x = 128, local_size_y = 1, local_size_z = 1) in;

uniform float time;

void main(){
	
	uint gid = gl_GlobalInvocationID.x;
	vec3 p = Position[gid].xyz;
	p = p+vec3(1,0,0);
	Position[gid].xyz = p;
	
	//Position[gid].xyz = Position[gid].xyz;
	//Velocities[gid].xyz = Velocities[gid].xyz
	//Colors[gid].xyz = Colors[gid].xyz;
}