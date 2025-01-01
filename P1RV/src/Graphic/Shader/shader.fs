#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Light light;

// texture sampler
uniform sampler2D texture1;

uniform vec3 viewPos;

void main()
{
    vec3 ambient = light.ambient;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm,lightDir),0.0);
	vec3 diffuse = light.diffuse * diff;

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),16 );
	vec3 specular = light.specular * spec;

	vec3 result = (ambient + diffuse + specular) * texture(texture1, TexCoord).xyz;
	FragColor = vec4(result, 1.0);
}