#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class InputHandler {
private:
	bool O_DOWN;
	bool O_UP;
	bool O_PRESS;
	bool I_DOWN;
	bool I_UP;
	bool I_PRESS;
	bool U_DOWN;
	bool U_UP;
	bool U_PRESS;
	bool L_DOWN;
	bool L_UP;
	bool L_PRESS;
	bool K_DOWN;
	bool K_UP;
	bool K_PRESS;
	bool J_DOWN;
	bool J_UP;
	bool J_PRESS;
public:
	double scale;
	double posx;
	double posy;
	bool LMBFirstPress;
	bool RMBFirstPress;
	bool LMBisPressed;
	double LMBposx;
	double LMBposy;
	int screenWidth, screenHeight;

	int iterations;

	InputHandler(GLFWwindow* window, int screenWidth, int screenHeight);
	void doInputs(GLFWwindow* window);
};
