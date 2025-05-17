#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

out vec4 ourColor;
out vec4 ourPos;

uniform float hOffset;

void main() {
	vec4 pos = vec4(aPos.x + hOffset, aPos.y, aPos.z, 1.0);
	gl_Position = pos;
	ourColor = aColor;
	ourPos = pos;
}
