#version 430

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 blendShape[10];

out vec2 geom_uv;
out vec3 geom_normal;
out vec3 geom_worldpos;
out vec3 geom_ViewPos;

uniform mat4 TransformMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform vec3 ViewPos;
uniform int BlendShapeCount;
uniform float Weights[10];

void main()
{
	//vec3 deltaPosition;
	//vec3 finalPose = position;
	//for(int i = 0; i < (BlendShapeCount); i++)
	//{
	//	//finalPose= mix(finalPose, blendShape[i], Weights[i] );
	//	deltaPosition = blendShape[i] - (position * (1.0f-Weights[i]));
	//	finalPose += Weights[i] * position * deltaPosition;
	//}
	
	vec3 finalPose/* = vec3(0.0f,0.0f,0.0f)*/;
	float neutral_w = 1.0;
	float sum_w = 0;
	float finalWeights[10];

	//if other weights add up to one, use neutral target
	for(int i = 0; i < (BlendShapeCount); i++)
	{
		neutral_w -= Weights[i];
	}
	clamp(neutral_w, 0.0, 1.0);

	//get a sum of weights
	for(int i = 0; i < (BlendShapeCount); i++)
	{
		sum_w += Weights[i];
	}
	sum_w += neutral_w;

	
	//work out factors for each target and use them for the final pos
	finalPose += position * (neutral_w/sum_w);
	for(int i = 0; i < (BlendShapeCount); i++)
	{
		finalPose += blendShape[i] * (Weights[i]/sum_w);
	}

	gl_Position = ProjectionMatrix * ViewMatrix * TransformMatrix * vec4(finalPose, 1);

	geom_uv = texCoord;
	geom_normal = normalize(mat3(TransformMatrix) * normal);
	geom_worldpos = vec3(TransformMatrix * vec4(finalPose, 1));
	geom_ViewPos = ViewPos;
}