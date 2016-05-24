#version 430
layout(rgba32f) uniform image2D destTex;
layout (local_size_x = 16, local_size_y = 16) in;
uniform float number;
uniform vec3 colorVector;

float rand(float number)
{
	//float2 noise = (frac(sin(dot(uv ,float(12.9898,78.233)*2.0)) * 43758.5453));
	//return abs(noise.x + noise.y) * 0.5;
	//vec2 p = floor
	return float(fract(sin(number) * 43758.5453123));
}

void main() {
	ivec2 storePos = ivec2(gl_GlobalInvocationID.xy);
	float globalCoef = sin(float(gl_WorkGroupID.x + gl_WorkGroupID.y) * number);
	float derp = mod(gl_WorkGroupID.y, 5);
	vec4 color = vec4(0,0,0,0);
	if(derp == 0)
	{
		 color = imageLoad(destTex,storePos) + vec4((colorVector) * 0.1, 1.0);
	}
	else
	{
		 color = imageLoad(destTex,storePos) + vec4((colorVector) * rand(globalCoef), 1.0);
	}
	imageStore(destTex, storePos,  color );
	memoryBarrier();
}