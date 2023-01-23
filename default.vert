#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 Color;

out vec2 textureCoord;

void main() {
	textureCoord = Color;
	gl_Position = vec4(0.8 * aPos, 1.0);
}
