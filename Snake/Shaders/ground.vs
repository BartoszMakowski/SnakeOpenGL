#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoord;

out vec4 vertexColor;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4(position, 1.0f);
	vertexColor = vec4(0.9f, 0.0f, 0.2f, 1.0f);
	texCoord = vec2(textureCoord.x, 1.0 - textureCoord.y);
}