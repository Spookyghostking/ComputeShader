#include <iostream>

#include "fileReader.h"
#include "Shader.h"
#include "ComputeShader.h"

static void errorCallbackFunction(int errorCode, const char* errorMessage) {
	std::cout << "Glfw error " << errorCode << ": " << errorMessage << std::endl;
}

int main() {
	GLfloat vertices[] = {
		-1.0, -1.0,  0.0, 0.0, 0.0,
		 1.0, -1.0,  0.0, 1.0, 0.0,
		 1.0,  1.0,  0.0, 1.0, 1.0,
		-1.0,  1.0,  0.0, 0.0, 1.0,
	};
	GLuint indices[] = {
		0, 1, 2,
		2, 3, 0,
	};
	
	int SCREEN_WIDTH = 1440, SCREEN_HEIGHT = 900;


	//glfwSetErrorCallback(errorCallbackFunction);
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initalize GLAD." << std::endl;
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	
	GLuint vertexArray, vertexBuffer, elementBuffer;
	glCreateVertexArrays(1, &vertexArray);
	glCreateBuffers(1, &vertexBuffer);
	glCreateBuffers(1, &elementBuffer);

	glBindVertexArray(vertexArray);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	GLuint screenTexture;
	glCreateTextures(GL_TEXTURE_2D, 1, &screenTexture);
	glTextureParameteri(screenTexture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(screenTexture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTextureParameteri(screenTexture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTextureParameteri(screenTexture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTextureStorage2D(screenTexture, 1, GL_RGBA32F, SCREEN_WIDTH, SCREEN_HEIGHT);
	glBindImageTexture(0, screenTexture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);

	// Shaders
	Shader shader = Shader("default.vert", "default.frag");
	ComputeShader computeShader = ComputeShader("default.comp");


	while (!glfwWindowShouldClose(window)) {
		// inputs

		// rendering
		glClearColor(0.1, 0.05, 0.12, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		computeShader.Activate(SCREEN_WIDTH, SCREEN_HEIGHT, 1, GL_ALL_BARRIER_BITS);

		shader.Activate();
		glBindTextureUnit(0, screenTexture);
		glUniform1i(glGetUniformLocation(shader.program, "screen"), 0);

		glBindVertexArray(vertexArray);
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);


		// update
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
