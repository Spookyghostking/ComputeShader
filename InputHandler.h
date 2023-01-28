#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class InputHandler {
public:
	float scale;
	float posx;
	float posy;
	bool LMBFirstPress;
	bool LMBisPressed;
	double LMBposx;
	double LMBposy;
	int screenWidth, screenHeight;

	InputHandler(GLFWwindow* window, int screenWidth, int screenHeight);
	void doInputs(GLFWwindow* window);
};
