#version 460 core

uniform sampler2D screen;
in vec2 textureCoord;

void main() {
	gl_FragColor = texture(screen, textureCoord);
	//gl_FragColor = vec4(textureCoord.x, 0.0, textureCoord.y, 1.0);
}