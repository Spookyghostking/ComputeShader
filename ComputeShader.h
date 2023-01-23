#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>

class ComputeShader {
public:
	// load file into a source code string
	// use string to compile a shader program
	// make all the functions needed to use the shader
	GLuint program;
	ComputeShader(const char* filename);

	void Activate(GLuint numGroupsX, GLuint numGroupsY, GLuint numGroupsZ, GLbitfield memoryBarriers);
	void Delete();
private:
	void compileErrors(GLuint shader, const char* type);
};