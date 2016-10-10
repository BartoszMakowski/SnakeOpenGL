#version 330

in vec3 position;
in vec2 textureCoord;
in vec3 normal;


out vec2 texCoord;
out vec3 Normal;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4(position, 1.0f);
	texCoord = vec2(textureCoord.x, 1.0 - textureCoord.y);
	fragPos = vec3(model * vec4(position, 1.0f));
	Normal = mat3(transpose(inverse(model))) * normal;  
}