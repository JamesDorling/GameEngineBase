/*! \file inputPoller.h
*/
#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace Engine
{
	/* \class InputPoller
	*	\brief input poller for specifically GLFW
	*/
	class GLFWInputPoller
	{
	public:
		static bool isKeyPressed(int32_t keyCode); //!< Is a key pressed
		static bool isMouseButtonPressed(int32_t mouseButton); //!< Is a mouse button pressed
		static glm::vec2 getMousePosition(); //!< Current mouse pos
		inline static float getMouseX() { return getMousePosition().x; } //!< Getter for the mouse position on the X axis
		inline static float getMouseY() { return getMousePosition().y; } //!< Getter for the mouse position on the Y axis
		static void setCurrentWindow(GLFWwindow* window) { s_window = window; } //!< Setter for the current window
	private:
		static GLFWwindow* s_window; //!< Current GLFW window

	};
}
