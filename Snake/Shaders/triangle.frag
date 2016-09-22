#version 330 core

in vec2 texCoord;

uniform vec4 ourColor;
uniform sampler2D ourTexture;

out vec4 color;

void main() {
	color = texture(ourTexture, texCoord);// * ourColor;
}