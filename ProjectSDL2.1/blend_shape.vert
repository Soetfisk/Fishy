#version 430

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3[10] blendShape;

out vec2 geom_uv;
out vec3 geom_normal;
out vec3 geom_worldpos;
out vec3 geom_ViewPos;

uniform mat4 TransformMatrix;
uniform mat4 ProjectionViewMatrix;
uniform vec3 ViewPos;
uniform int BlendShapeCount;
uniform float Weights[10];

void main()
{
	

	vec3 deltaPosition;
	vec3 finalPose = position;

	for(int i = 0; i < (BlendShapeCount); i++)
	{
		deltaPosition = blendShape[i] - position;
		finalPose += Weights[i] * blendShape[i] * deltaPosition;
	}

	gl_Position = ProjectionViewMatrix * TransformMatrix * vec4(finalPose, 1);

	geom_uv = texCoord;
	geom_normal = normalize(mat3(TransformMatrix) * normal);
	geom_worldpos = vec3(TransformMatrix * vec4(finalPose, 1));
	geom_ViewPos = ViewPos;
}