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
uniform mat4 ProjectionViewMatrix;
uniform vec3 ViewPos;
uniform int BlendShapeCount;
uniform float Weights[10];

void main()
{
	

	vec3 deltaPosition;
	vec3 finalPose = position;

	//for(int i = 0; i < (BlendShapeCount); i++)
	//{
	//deltaPosition = blendShape.xyz - position.xyz;
	//finalPose += 1.0 * blendShape.xyz * deltaPosition.xyz;
	//}

	gl_Position = ProjectionViewMatrix * TransformMatrix * vec4(blendShape[6], 1);

	geom_uv = texCoord;
	geom_normal = normalize(mat3(TransformMatrix) * normal);
	geom_worldpos = vec3(TransformMatrix * vec4(blendShape[6], 1));
	geom_ViewPos = ViewPos;
}