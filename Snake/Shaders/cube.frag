#version 330 core

in vec2 texCoord;

uniform sampler2D ourTexture;
uniform vec3 lightColor;

out vec4 color;

void main() {
	float ambientStrength = 0.6f;
	//vec3 ambient = ambientStrength * lightColor;
	//vec3 result = ambient * texture(ourTexture, texCoord);
	//color = vec4(result, 1.0f);

	//color = texture(ourTexture, texCoord) * vec4(vec3(1.0f, 0.5f, 1.0f), 1.0f);
	color = texture(ourTexture, texCoord) * vec4(lightColor, 1.0f);
	color *= ambientStrength;
	//color = texture(ourTexture, texCoord);
}