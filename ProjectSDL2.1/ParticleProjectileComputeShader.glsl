#version 430 compatibility

#extension GL_ARB_compute_shader : enable
#extension GL_ARB_shader_storage_buffer_object : enable



layout( std140, binding=4 ) buffer transformMatrix {
	mat4 transMatrix[];
};

layout(std140, binding = 5) buffer Vel{
	vec4 Velocities[];
};

layout(local_size_x = 128, local_size_y = 1, local_size_z = 1) in;

void main(){
	
	uint gid = gl_GlobalInvocationID.x;

	mat4 tm = transMatrix[gid]
	tm = tm * velocities[gid];
	
	//Position[gid].xyz = Position[gid].xyz;
	//Velocities[gid].xyz = Velocities[gid].xyz
	//Colors[gid].xyz = Colors[gid].xyz;
}