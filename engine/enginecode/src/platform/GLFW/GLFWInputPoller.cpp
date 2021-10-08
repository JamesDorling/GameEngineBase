/* \file GLFWInputPoller.cpp */
#include "engine_pch.h"
#include "platform/GLFW/GLFWInputPoller.h"

namespace Engine
{
	GLFWwindow* GLFWInputPoller::s_window = nullptr; //!< Initialiser for the window
	bool GLFWInputPoller::isKeyPressed(int32_t keyCode) 
	{
		if (s_window)
		{
			auto ans = glfwGetKey(s_window, keyCode); //!< Get the keycode
			return ans == GLFW_PRESS || ans == GLFW_REPEAT; //!< Return the button being pressed or repeated
		}
		return false;
	}
	bool GLFWInputPoller::isMouseButtonPressed(int32_t mouseButton)
	{
		if (s_window)
		{
			auto ans = glfwGetMouseButton(s_window, mouseButton); //!< Get the mouse button
			return ans == GLFW_PRESS; //!< Return the button is pressed
		}
		return false;
	}
	glm::vec2 GLFWInputPoller::getMousePosition()
	{
		if (s_window)
		{
			double x, y; //!< Pre-define the x and y coordinates
			glfwGetCursorPos(s_window, &x, &y); //!< Get the cursor position
			glm::vec2 ans = glm::vec2(static_cast<float>(x), static_cast<float>(y)); //!< Turn the x and y coordinates into a vec 2
			return ans; //!< return the vec2
		}
		return glm::vec2(-1.f, -1.f); //!< Else return off the window
	}
}