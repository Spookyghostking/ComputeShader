#include "ComputeShader.h"
#include "fileReader.h"

ComputeShader::ComputeShader(const char* filename)
{
	std::string sourceString = get_file_contents(filename);
	const char* source = sourceString.c_str();

	GLuint shader = glCreateShader(GL_COMPUTE_SHADER);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	compileErrors(shader, "COMPUTE SHADER");

	program = glCreateProgram();
	glAttachShader(program, shader);
	glLinkProgram(program);
	compileErrors(program, "SHADER PROGRAM");

	//glDeleteShader(shader);
}

void ComputeShader::Activate(GLuint numGroupsX, GLuint numGroupsY, GLuint numGroupsZ, GLbitfield memoryBarriers = GL_ALL_BARRIER_BITS)
{
	glUseProgram(program);
	glDispatchCompute(numGroupsX, numGroupsY, numGroupsZ);
	if (memoryBarriers != NULL) {
		glMemoryBarrier(memoryBarriers);
	}
}

void ComputeShader::Delete()
{
	glDeleteProgram(program);
}

void ComputeShader::compileErrors(GLuint shader, const char* type) {
	GLint hasCompiled;
	char infolog[1024];
	if (type != "SHADER PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			glGetShaderInfoLog(shader, 1024, NULL, infolog);
			std::cout << "SHADER COMPILE ERROR FOR COMPUTE " << type << ":\n" << infolog << std::endl;
		}
	}
	else {
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			glGetProgramInfoLog(shader, 1024, NULL, infolog);
			std::cout << "SHADER LINKING ERROR FOR " << type << ": " << infolog << std::endl;
		}
	}
}