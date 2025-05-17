#version 410 core

out vec4 FragColor;

in vec4 ourColor;
in vec4 ourPos;

uniform float time;

void main() {
	FragColor = ourPos;
}
