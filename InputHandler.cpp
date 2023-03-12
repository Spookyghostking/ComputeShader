#include <iostream>
#include "InputHandler.h"

static int scroll = 0;

void scrollFunc(GLFWwindow* window, double xoffset, double yoffset) {
	scroll += (int)yoffset;
}

InputHandler::InputHandler(GLFWwindow* window, int screenWidth, int screenHeight) {
	glfwSetScrollCallback(window, scrollFunc);
	scale = 1.0f;
	posx = 0.0f;
	posy = 0.0f;
	LMBFirstPress = true;
	LMBisPressed = false;
	LMBposx = 0.0;
	LMBposy = 0.0;
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
}

void InputHandler::doInputs(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		std::cout << "press" << std::endl;
	}
	// camera pan
	LMBisPressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS;
	if (LMBisPressed) {
		if (LMBFirstPress) {
			LMBFirstPress = false;
			glfwGetCursorPos(window, &LMBposx, &LMBposy);
		}
		else {
			double newposx, newposy, diffx, diffy;
			glfwGetCursorPos(window, &newposx, &newposy);
			diffx = newposx - LMBposx;
			diffy = newposy - LMBposy;
			LMBposx = newposx;
			LMBposy = newposy;
			posx += 2 * diffx / (screenWidth * scale);
			posy += 2 * diffy / (screenHeight * scale);
		}
	}
	else {
		if (!LMBFirstPress) {
			LMBFirstPress = true;
		}
		glfwGetCursorPos(window, &LMBposx, &LMBposy);
	}

	bool RMBisPressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS;
	if (RMBisPressed) {
		if (RMBFirstPress) {
			RMBFirstPress = false;
			//double posx, posy;
			//glfwGetCursorPos(window, &posx, &posy);
			std::cout << "x: " << posx << "\ty: " << posy << std::endl;

		}
	}
	else {
		if (!RMBFirstPress) {
			RMBFirstPress = true;
		}
		//glfwGetCursorPos(window, &LMBposx, &LMBposy);
	}

	// camera zoom
	while (scroll != 0) {
		if (scroll > 0) {
			scale *= 1.1;
			scroll -= 1;
		}
		else {
			scale *= 0.9090909090909090;
			scroll += 1;
		}
	}
}

