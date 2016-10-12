#version 330

in vec2 texCoord;
in vec3 Normal;
in vec3 fragPos;

uniform sampler2D ourTexture;
uniform vec3 light1Color;
uniform vec3 light1Pos;
uniform vec3 light2Color;
uniform vec3 light2Pos;
uniform vec3 viewPos;

out vec4 color;

vec3 phongLight(vec3 lightPos, vec3 viewPos, vec3 lightColor, vec3 normal, vec3 objectColor){
	float ambientStrength = 0.5f;
    vec3 ambient = lightColor * ambientStrength;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	float specularStrength = 0.3f;
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8);
	vec3 specular = specularStrength * spec * lightColor;
	return(ambient + diffuse + specular);	
}

void main() {
	vec3 objectColor =  vec3(texture(ourTexture, texCoord));
	vec3 phong1 = phongLight(light1Pos, viewPos, light1Color, Normal, objectColor);
	vec3 phong2 = phongLight(light2Pos, viewPos, light2Color, Normal, objectColor);
	vec3 result = (phong1 + phong2) * objectColor;	
    color = vec4(result, 1.0f);

}