#version 460 core

uniform sampler2D screen;
in vec2 textureCoord;

void main() {
	gl_FragColor = texture(screen, textureCoord);
}