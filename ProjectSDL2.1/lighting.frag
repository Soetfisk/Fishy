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
uniform vec3 ViewPos;

vec3 CalcDirLight(Light light, vec3 normal, vec3 viewDir, vec3 FragPos);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir); 

void main()
{
	PointLight l;
	l.position = vec3(3, 0, 3);
	l.constant = 1.0f;
	l.linear =  0.14f;
	l.quadratic = 0.07;
	l.ambient = vec3(0.25f, 0.15, 0.04);
	l.diffuse = vec3(1.0f, 0.58, 0.16);
	l.specular = vec3(0.5f, 0.0f, 0.0f);

	vec3 Output = vec3(0);

	vec3 FragPos = texture(posTexture, frag_uv).rgb;
	vec3 Normal = texture(normalTexture, frag_uv).rgb;

	vec3 viewDir = normalize(ViewPos - FragPos);
	
	Output += CalcDirLight(dirLight, Normal, viewDir, FragPos);

	for(int i = 0; i < NR_POINT_LIGHTS; i++)
		Output += CalcPointLight(pointLights[i], Normal, FragPos, viewDir);

	float fogFactor = 0;
	float fogEnd = 100;
	float fogStart = 30;
	vec3 fogColor = vec3(0.1,0.1,0.1);
	//68
	fogFactor = (fogEnd-texture(distTexture, frag_uv).r) / (fogEnd - fogStart);
	fogFactor = clamp(fogFactor,0.0,1.0);

	Output = clamp(mix(fogColor, Output, fogFactor),0.0,1.0);

	color = vec4(Output, 1);
}
vec3 CalcDirLight(Light light, vec3 normal, vec3 viewDir, vec3 FragPos)
{
	vec3 lightDir = normalize(light.dir);

	float diff = max(dot(normal, lightDir), 0.0);
	
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

	vec3 ambient	= light.ambient;
	vec3 diffuse	= (diff * light.diffuse) ;
	vec3 specular	= light.specular * (spec) * texture(colorTexture, frag_uv).a;

	return (ambient + (diffuse)) * texture(colorTexture, frag_uv).rgb;
}
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
		vec3 lightDir = normalize(light.position - fragPos);

		float diff = max(dot(normal, lightDir), 0.0);

		vec3 reflectDir = reflect(-lightDir, normal);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
		
		float dist    = length(light.position - fragPos);
		float attenuation = 1.0f / (light.constant + light.linear * dist + 
  									light.quadratic * (dist * dist)); 

		vec3 ambient	= light.ambient * texture(colorTexture, frag_uv).rgb;
		vec3 diffuse	= (diff * light.diffuse * texture(colorTexture, frag_uv).rgb);
		vec3 specular	= light.specular * (spec) * texture(colorTexture, frag_uv).a;
		ambient  *= attenuation;
		diffuse  *= attenuation;
		specular *= attenuation;

		return clamp((ambient + diffuse),0.0,1.0);
}