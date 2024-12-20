#version 330 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};
			
struct DirLight {		
	vec3 direction;
				
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
			
struct PointLight {
	vec3 position;
				
	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight {
	vec3 position;
	vec3 direction;
				
	float cutOff;
	float outerCutOff;
				
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

#define NR_POINT_LIGHTS 4
			
uniform DirLight dirLight; // 方向光
uniform PointLight pointLights[NR_POINT_LIGHTS]; // 点光源
uniform SpotLight spotLight; // 聚光
uniform Material material;
			
layout(location = 0) out vec4 color;	

in vec3 v_Normal;
in vec3 v_Pos;
in vec2 v_TexCoord;
			
uniform vec3 objectColor;
uniform vec3 lightColor;	
uniform vec3 viewPos;

vec3 CalDirLight(DirLight light, vec3 normal, vec3 viewDir);

vec3 CalPointLight(PointLight light, vec3 normal, vec3 vpos, vec3 viewDir);

vec3 CalSpotLight(SpotLight light, vec3 normal, vec3 vpos, vec3 viewDir);
			
void main()
{	
	// 属性
	vec3 norm = normalize(v_Normal);
	vec3 viewDir = normalize(viewPos - v_Pos);

	// 定向光
	vec3 result = CalDirLight(dirLight, norm, viewDir);
				
	// 点光源
	for (int i = 0; i < NR_POINT_LIGHTS; i++) 
		result += CalPointLight(pointLights[i], norm, v_Pos, viewDir);
	// 聚光
		result += CalSpotLight(spotLight, norm, v_Pos, viewDir);

	color = vec4(result, 1.0f);
}

vec3 CalDirLight(DirLight light, vec3 normal, vec3 viewDir) 
{
				
	vec3 lightDir = normalize(-light.direction);
	// 漫反射着色
	float diff = max(dot(normal, lightDir), 0.0f);
	// 镜面光着色
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0), material.shininess);
	// 合并结果
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, v_TexCoord));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, v_TexCoord));
	vec3 specular = light.specular  * spec * vec3(texture(material.diffuse, v_TexCoord));
	return (ambient + diffuse + specular);
}

vec3 CalPointLight(PointLight light, vec3 normal, vec3 vpos, vec3 viewDir) 
{
				
	vec3 lightDir = normalize(light.position - vpos);
	// 漫反射着色
	float diff = max(dot(normal, lightDir), 0.0f);
	// 镜面光着色
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0), material.shininess);
	// 合并结果
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, v_TexCoord));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, v_TexCoord));
	vec3 specular = light.specular  * spec * vec3(texture(material.diffuse, v_TexCoord));
	// 衰减
	float distance = length(light.position - vpos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
				
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}

vec3 CalSpotLight(SpotLight light, vec3 normal, vec3 vpos, vec3 viewDir) {
	vec3 lightDir = normalize(light.position - vpos);
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
				
	// 漫反射着色
	float diff = max(dot(normal, lightDir), 0.0f);
	// 镜面光着色
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0), material.shininess);
	// 合并结果
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, v_TexCoord));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, v_TexCoord));
	vec3 specular = light.specular  * spec * vec3(texture(material.diffuse, v_TexCoord));
			
	diffuse *= intensity;
	specular *= intensity;

	return (ambient + diffuse + specular);
}