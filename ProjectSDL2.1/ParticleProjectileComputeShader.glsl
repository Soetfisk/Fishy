#version 430 compatibility

#extension GL_ARB_compute_shader :				 enable
#extension GL_ARB_shader_storage_buffer_object : enable

struct Particle{
	vec4 position;
	vec4 velocity;
	vec4 acceleration;
	float scale;
	bool alive;
};



layout( std430, binding=6 ) buffer Part
{
	Particle particles[ ]; // array of structures
};

uniform float DT;

layout(local_size_x = 128, local_size_y = 1, local_size_z = 1) in;

void main(){
	
	if(alive == true){
		const vec4 SPHERE = vec4( -100., -800., 0., 600. ); // x, y, z, r 

		const vec3 G = vec3(0.f,-9.8f,0.f);
	

		uint gid = gl_GlobalInvocationID.x;
		vec3 p = particles[gid].position.xyz;
		vec3 v = particles[gid].velocity.xyz;

		vec3 pp = p + (v*DT) + .5*DT*DT*G;
		vec3 vp = v+ G*DT;


		particles[gid].position.xyz = pp;
		particles[gid].velocity.xyz = vp;
	}
	else{
		particles[gid].position = particles[gid].position;
		particles[gid].velocity = particles[gid].velocity;
	}
	

}

