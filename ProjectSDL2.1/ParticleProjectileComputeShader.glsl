#version 430 compatibility

#extension GL_ARB_compute_shader :				 enable
#extension GL_ARB_shader_storage_buffer_object : enable

struct Particle{
	vec4 position;
	vec4 velocities;
	vec4 customVariables; //x=scale, y = currentLifeTime
};



layout( std430, binding=6 ) buffer Part
{
	Particle particles[ ]; // array of structures
};

uniform float DT;

layout(local_size_x = 128, local_size_y = 1, local_size_z = 1) in;

vec3 Bounce(vec3 vin, vec3 n){
	vec3 vout = reflect(vin, n);
	return vout;
}

vec3 BounceSphere(vec3 p, vec3 v, vec4 s){
	vec3 n = normalize(p-s.xyz);
	return Bounce(v, n);
}

bool IsInsideSphere(vec3 p, vec4 s){
	float r = length(p-s.xyz);
	return (r<s.w);
}

void main(){
	const vec4 SPHERE = vec4( -100., -800., 0., 600. ); // x, y, z, r 

	const vec3 G = vec3(0.f,-9.8f,0.f);
	
	
	uint gid = gl_GlobalInvocationID.x;

	float scale = particles[gid].customVariables.x;
	vec3 p = particles[gid].position.xyz;
	vec3 v = particles[gid].velocities.xyz;

	vec3 pp = p + (v*DT) + .5*DT*DT*G;
	vec3 vp = v+ G*DT;

	
	////if(IsInsideSphere(pp, SPHERE)){
	//	vp = BounceSphere(p, v, SPHERE);
	//	pp = p + (v*DT) + .5*DT*DT*G;
	////}


	particles[gid].position.xyz = pp;
	particles[gid].velocities.xyz = vp;
	particles[gid].customVariables.x = scale;

}

