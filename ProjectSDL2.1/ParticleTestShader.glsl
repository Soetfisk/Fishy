#version 430 compatibility

#extension GL_ARB_compute_shader :				 enable
#extension GL_ARB_shader_storage_buffer_object : enable

struct Particle{
	vec4 position;
	vec4 emiterPosition;
	vec4 velocity;
	vec4 customVariables; //x= scale, y=lifeTime
	vec4 acceleration;
};

layout( std430, binding=6 ) buffer Part
{
	Particle particles[ ]; // array of structures
};

uniform float DT;

layout(local_size_x = 128, local_size_y = 1, local_size_z = 1) in;


void main(){
	uint gid = gl_GlobalInvocationID.x;
	float isAlive = particles[gid].customVariables.w;

	if(isAlive == 1){

		float lifeTime = particles[gid].customVariables.y;
		if(lifeTime>0){
			const vec3 G = vec3(0.f,-.38f,0.f);
			float scale = particles[gid].customVariables.x;
			float speed = particles[gid].customVariables.z;
			vec3 acc = particles[gid].acceleration.xyz;
	
			vec3 p = particles[gid].position.xyz;
			vec3 v = particles[gid].velocity.xyz;

			vec3 pp = p + ((v*DT) + .5*DT*DT*acc)*speed;;
			vec3 vp = v+ (acc*DT)*speed;

			particles[gid].position.xyz = pp;
			particles[gid].velocity.xyz = vp;
			particles[gid].customVariables.y -= DT;
		}
		else{
			particles[gid].position.xyz = particles[gid].emiterPosition.xyz;
			particles[gid].customVariables.y = 5;
			//particles[gid].customVariables.w = 0;
		}

	}

	
	
}

