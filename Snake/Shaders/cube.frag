#version 330 core

in vec2 texCoord;
in vec3 Normal;
in vec3 fragPos;

uniform sampler2D ourTexture;
uniform vec3 lightColor;
uniform vec3 lightPos;

out vec4 color;

void main() {
	float ambientStrength = 0.5f;
    vec3 ambient = lightColor * ambientStrength;
	vec3 objectColor =  vec3(texture(ourTexture, texCoord));


	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 result = (ambient + diffuse) * objectColor;
    color = vec4(result, 1.0f);


	//color = texture(ourTexture, texCoord) * ambient;
	//color *= ambientStrength;
	//color = texture(ourTexture, texCoord);
}