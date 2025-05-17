#version 410 core

out vec4 FragColor;

in vec4 ourColor;

uniform float time;

void main() {
	FragColor = mix(vec4(1.0, 1.0, 0.0, 1.0), ourColor, sin(time) / 2.0 + 0.5);
}
