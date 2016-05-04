#version 430 compatibility

#extension GL_ARB_compute_shader :				 enable
#extension GL_ARB_shader_storage_buffer_object : enable

struct Particle{
	vec4 position;
	float scale;
	vec4 emiterPosition;
	float lifeTime;
	vec4 velocity;
};



layout( std430, binding=6 ) buffer Part
{
	Particle particles[ ]; // array of structures
};

uniform float DT;

layout(local_size_x = 128, local_size_y = 1, local_size_z = 1) in;

float rand(vec2 co){
  return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main(){
	uint gid = gl_GlobalInvocationID.x;
	if(particles[gid].lifeTime>0){
		const vec3 G = vec3(0.f,-3.8f,0.f);
		

	
		vec3 p = particles[gid].position.xyz;
		vec3 v = particles[gid].velocity.xyz;

		vec3 pp = p + (v*DT) + .5*DT*DT*G;
		vec3 vp = v+ G*DT;

	
		////if(IsInsideSphere(pp, SPHERE)){
		//	vp = BounceSphere(p, v, SPHERE);
		//	pp = p + (v*DT) + .5*DT*DT*G;
		////}


		particles[gid].position.xyz = pp;
		particles[gid].velocity.xyz = vp;
		particles[gid].lifeTime-= DT;
	}
	else{
		float randomNr = rand(vec2(0,3));
		particles[gid].position.xyz = particles[gid].emiterPosition.xyz + vec3(randomNr);
		particles[gid].lifeTime = 2;
	}
	
}

