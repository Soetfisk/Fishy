#version 450

layout(location = 0) in position;
layout(location = 1) in texCoord;
layout(location = 2) in normal

out test_pos;
out test_texCoord;
out test_normal;

uniform mat4 TransformMatrix;
uniform mat4 ProjectionViewMatrix;
uniform mat4 ViewPos

int main()
{

}