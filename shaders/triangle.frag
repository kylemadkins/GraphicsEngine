#version 410 core

out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
	vec2 flippedTexCoord = vec2(texCoord.x * -1, texCoord.y);
	vec4 color1 = texture(texture1, flippedTexCoord);
	vec4 color2 = texture(texture2, flippedTexCoord);
	float alpha = color2.a * 0.4;
	FragColor = mix(color1, color2, alpha);
}
