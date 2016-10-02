#version 330 core

in vec2 texCoord;
in vec3 Normal;
in vec3 fragPos;

uniform sampler2D ourTexture;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

out vec4 color;

void main() {
	vec3 objectColor =  vec3(texture(ourTexture, texCoord));

	float ambientStrength = 0.5f;
    vec3 ambient = lightColor * ambientStrength;	

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	float specularStrength = 0.7f;
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8);
	vec3 specular = specularStrength * spec * lightColor;

	vec3 result = (ambient + diffuse + specular) * objectColor;
    color = vec4(result, 1.0f);


	//color = texture(ourTexture, texCoord) * ambient;
	//color *= ambientStrength;
	//color = texture(ourTexture, texCoord);
}