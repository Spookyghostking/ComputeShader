#include "Shader.h"
#include "fileReader.h"

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexSourceString = get_file_contents(vertexFile);
	const char* vertexSource = vertexSourceString.c_str();

	std::string fragmentSourceString = get_file_contents(fragmentFile);
	const char* fragmentSource = fragmentSourceString.c_str();

	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexSource, NULL);
	glCompileShader(vertex);
	compileErrors(vertex, "VERTEX SHADER");

	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentSource, NULL);
	glCompileShader(fragment);
	compileErrors(fragment, "FRAGMENT SHADER");

	program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);
	compileErrors(program, "SHADER PROGRAM");

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::Activate() {
	glUseProgram(program);
}

void Shader::Delete() {
	glDeleteProgram(program);
}

void Shader::compileErrors(GLuint shader, const char* type) {
	GLint hasCompiled;
	char infolog[1024];
	if (type != "SHADER PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			glGetShaderInfoLog(shader, 1024, NULL, infolog);
			std::cout << "SHADER COMPILE ERROR FOR " << type << ":\n" << infolog << std::endl;
		}
	}
	else {
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			glGetProgramInfoLog(shader, 1024, NULL, infolog);
			std::cout << "SHADER LINKING ERROR FOR " << type << ":\n" << infolog << std::endl;
		}
	}
}