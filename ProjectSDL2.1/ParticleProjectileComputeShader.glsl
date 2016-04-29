#version 430 compatibility

#extension GL_ARB_compute_shader : enable
#extension GL_ARB_shader_storage_buffer_object : enable

//struct Particle{
//	mat4 transformMatrix;
//	vec4 position;
//	vec4 velocities;
//};
struct Particle{
	mat4 transformMatrix;
	vec4 position;
	vec4 velocities;
};

layout( std140, binding=4 ) buffer transformMatrix {
	mat4 transMatrix[];
};

layout(std430, binding = 5) buffer Vel{
	vec4 Velocities[];
};

layout(std430, binding = 6) buffer positions{
	Particle particles[];
};


layout(local_size_x = 128, local_size_y = 1, local_size_z = 1) in;

void main(){
	
	uint gid = gl_GlobalInvocationID.x;
	vec3 p = particles[gid].position.xyz;
	p = p+vec3(1,0,0);
	particles[gid].position.xyz = p;
	particles[gid].transformMatrix = mat4(1);
	//Position[gid].xyz = Position[gid].xyz;
	//Velocities[gid].xyz = Velocities[gid].xyz
	//Colors[gid].xyz = Colors[gid].xyz;
}