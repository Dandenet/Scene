#version 460 core

struct Material {
	sampler2D diffuse;
	vec3 specular;
	float shinines;
};

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec2 textureCoord;
in vec3 fragPos;
in vec3 Normal;

out vec4 FragColor;
uniform Light u_light;
uniform Material u_material;
uniform vec3 u_viewPos; // camera position


void main()
{
	vec3 lightDir = normalize(u_light.position - fragPos);
	vec3 viewDir = normalize(u_viewPos - fragPos);
	vec3 normal = normalize(Normal);

	// ambient lighting
	vec3 ambient = u_light.ambient * vec3(texture(u_material.diffuse, textureCoord));

	// diffuse lighting
	float diff = max(dot(normal, lightDir), 0.);
	vec3 diffuse = u_light.diffuse * diff * vec3(texture(u_material.diffuse, textureCoord));

	// specular lighting
	vec3 refDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, refDir), 0.0), u_material.shinines);
	vec3 specular = spec * u_light.specular * vec3(texture(u_material.diffuse, textureCoord));

	// result lighting
	FragColor = vec4(ambient + diffuse + specular, 1.);
}
