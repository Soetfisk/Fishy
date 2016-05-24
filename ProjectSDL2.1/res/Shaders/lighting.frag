#version 430

struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Light
{
	vec3  dir;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec2 frag_uv;

out vec4 color;

#define NR_POINT_LIGHTS 30
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform Light dirLight;

uniform sampler2D colorTexture;
uniform sampler2D posTexture;
uniform sampler2D normalTexture;
uniform sampler2D distTexture;
uniform sampler2D ambientTexture;
uniform sampler2D specularTexture;
uniform vec3 ViewPos;
uniform float fogEndFloat;
uniform float fogStartFloat;
uniform vec3 fogColorVector;

vec3 CalcDirLight(Light light, vec3 normal, vec3 viewDir, vec3 FragPos);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir); 

void main()
{
	vec3 Output = 0.3f * texture(colorTexture, frag_uv).rgb;

	vec3 FragPos = texture(posTexture, frag_uv).rgb;
	vec3 Normal = texture(normalTexture, frag_uv).rgb;

	vec3 viewDir = normalize(ViewPos - FragPos);
	
	Output += CalcDirLight(dirLight, Normal, viewDir, FragPos);

	for(int i = 0; i < NR_POINT_LIGHTS; i++)
		Output += CalcPointLight(pointLights[i], Normal, FragPos, viewDir);

	float fogFactor = 0;
	//68
	fogFactor = (fogEndFloat-texture(distTexture, frag_uv).r) / (fogEndFloat - fogStartFloat);
	fogFactor = clamp(fogFactor,0.0,1.0);

	Output = clamp(mix(fogColorVector, Output, fogFactor),0.0,1.0);

	color = vec4(Output, 1);
}
vec3 CalcDirLight(Light light, vec3 normal, vec3 viewDir, vec3 FragPos)
{
	vec3 lightDir = normalize(light.dir);

	float diff = max(dot(normal, lightDir), 0.0);
	
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

		vec3 ambient	= light.ambient * texture(ambientTexture, frag_uv).rgb;
		vec3 diffuse	= (diff * light.diffuse * texture(colorTexture, frag_uv).rgb);
		vec3 specular	= light.specular * (spec) * texture(specularTexture, frag_uv).rgb;

	return (ambient + diffuse + specular);
}
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
		vec3 lightDir = normalize(light.position - fragPos);

		float diff = max(dot(normal, lightDir), 0.0);

		vec3 reflectDir = reflect(-lightDir, normal);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), texture(specularTexture, frag_uv).a);
		
		float dist    = length(light.position - fragPos);
		float attenuation = 1.0f / (light.constant + light.linear * dist + 
  									light.quadratic * (dist * dist)); 

		vec3 ambient	= light.ambient * texture(ambientTexture, frag_uv).rgb;
		vec3 diffuse	= (diff * light.diffuse * texture(colorTexture, frag_uv).rgb);
		vec3 specular	= light.specular * (spec) * texture(specularTexture, frag_uv).rgb;
		ambient  *= attenuation;
		diffuse  *= attenuation;
		specular *= attenuation;

		return clamp((ambient + diffuse + specular),0.0,1.0);
}