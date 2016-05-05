#version 430

in vec2 texCoords;
out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{
	if(texture2D(text, texCoords).r < 0.2)
		discard;
	color = vec4(textColor, 1.0);
}