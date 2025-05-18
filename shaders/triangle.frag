#version 410 core

out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
	vec4 color1 = texture(texture1, texCoord);
	vec4 color2 = texture(texture2, texCoord);
	float alpha = color2.a * 0.2;
	FragColor = mix(color1, color2, alpha);
}
