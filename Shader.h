#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>

class Shader {
public:
	// load file into a source code string
	// use string to compile a shader program
	// make all the functions needed to use the shader
	GLuint program;
	Shader(const char* vertexFile, const char* fragmentFile);

	void Activate();
	void Delete();
private:
	void compileErrors(GLuint shader, const char* type);
};