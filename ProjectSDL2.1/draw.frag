#version 430

in vec2 frag_uv;
in vec3 frag_normal;
in vec3 frag_worldpos;
in vec3 frag_ViewPos;

uniform sampler2D diffuseTexture;
uniform vec3 diffuse;
uniform vec3 ambient;
uniform vec3 specular;
uniform float shininess;

out vec4 color;

void main()
{
	vec3 lightPos = vec3(1,20,1);

	color = texture2D(diffuseTexture, frag_uv);

	vec3 lightDir = normalize(lightPos - frag_worldpos);

	float diff = max(dot(frag_normal, lightDir), 0.0);
	
	vec3 reflectDir = reflect(-lightDir, frag_normal);
	float spec = pow(max(dot(normalize(frag_ViewPos - frag_worldpos), reflectDir), 0.0), shininess);

	vec3 ambient	= vec3(0.25, 0.61, 1) * ambient;
	vec3 diffuse	= (diff * vec3(0.25, 0.61, 1) * diffuse * texture(diffuseTexture, frag_uv).rgb);
	vec3 specular	= vec3(0.25, 0.61, 1) * (spec) * specular;

	color = vec4((ambient + diffuse + specular),1);
	//color = vec4((ambient + diffuse + specular),1);
}