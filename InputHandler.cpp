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

	O_DOWN= false;
	O_UP = false;
	O_PRESS= false;
	I_DOWN = false;
	I_UP = false;
	I_PRESS = false;
	U_DOWN = false;
	U_UP = false;
	U_PRESS = false;
	L_DOWN= false;
	L_UP = false;
	L_PRESS= false;
	K_DOWN = false;
	K_UP = false;
	K_PRESS = false;
	J_DOWN = false;
	J_UP = false;
	J_PRESS = false;

	iterations = 10;
}

void InputHandler::doInputs(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		std::cout << "press" << std::endl;
	}

	// change iteration number
#pragma region O_button
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
		if (!O_DOWN && !O_PRESS) {
			O_DOWN = true;
		}
		if (O_DOWN && O_PRESS) {
			O_DOWN = false;
		}
		O_PRESS = true;
	}
	else {
		if (O_PRESS) {
			O_UP = true;
		}
		if (O_UP && !O_PRESS) {
			O_UP = false;
		}
		O_PRESS = false;
	}
#pragma endregion
#pragma region I_button
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
		if (!I_DOWN && !I_PRESS) {
			I_DOWN = true;
		}
		if (I_DOWN && I_PRESS) {
			I_DOWN = false;
		}
		I_PRESS = true;
	}
	else {
		if (I_PRESS) {
			I_UP = true;
		}
		if (I_UP && !I_PRESS) {
			I_UP = false;
		}
		I_PRESS = false;
	}
#pragma endregion
#pragma region U_button
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
		if (!U_DOWN && !U_PRESS) {
			U_DOWN = true;
		}
		if (U_DOWN && U_PRESS) {
			U_DOWN = false;
		}
		U_PRESS = true;
	}
	else {
		if (U_PRESS) {
			U_UP = true;
		}
		if (U_UP && !U_PRESS) {
			U_UP = false;
		}
		U_PRESS = false;
	}
#pragma endregion
#pragma region L_button
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
		if (!L_DOWN && !L_PRESS) {
			L_DOWN = true;
		}
		if (L_DOWN && L_PRESS) {
			L_DOWN = false;
		}
		L_PRESS = true;
	}
	else {
		if (L_PRESS) {
			L_UP = true;
		}
		if (L_UP && !L_PRESS) {
			L_UP = false;
		}
		L_PRESS = false;
	}
#pragma endregion
#pragma region K_button
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
		if (!K_DOWN && !K_PRESS) {
			K_DOWN = true;
		}
		if (K_DOWN && K_PRESS) {
			K_DOWN = false;
		}
		K_PRESS = true;
	}
	else {
		if (K_PRESS) {
			K_UP = true;
		}
		if (K_UP && !K_PRESS) {
			K_UP = false;
		}
		K_PRESS = false;
	}
#pragma endregion
#pragma region J_button
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
		if (!J_DOWN && !J_PRESS) {
			J_DOWN = true;
		}
		if (J_DOWN && J_PRESS) {
			J_DOWN = false;
		}
		J_PRESS = true;
	}
	else {
		if (J_PRESS) {
			J_UP = true;
		}
		if (J_UP && !J_PRESS) {
			J_UP = false;
		}
		J_PRESS = false;
	}
#pragma endregion

	if (O_UP) {
		iterations += 1;
	}
	if (L_UP) {
		iterations -= 1;
	}
	if (I_UP) {
		iterations += 10;
	}
	if (K_UP) {
		iterations -= 10;
	}
	if (U_UP) {
		iterations += 100;
	}
	if (J_UP) {
		iterations -= 100;
	}
	if (iterations < 1) {
		iterations = 1;
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

