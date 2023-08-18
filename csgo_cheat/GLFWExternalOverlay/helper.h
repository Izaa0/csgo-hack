#pragma once
#include "GLFW/glfw3.h"
#include <iostream>


void ShowMenu(GLFWwindow* Window)
{
	std::cout << "Showing Menu \n";
	glfwSetWindowAttrib(Window, GLFW_MOUSE_PASSTHROUGH, false);
}

void HideMenu(GLFWwindow* Window)
{
	std::cout << "Hiding Menu \n";
	glfwSetWindowAttrib(Window, GLFW_MOUSE_PASSTHROUGH, true);
}