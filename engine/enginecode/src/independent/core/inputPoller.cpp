/* \file inputPoller.cpp  */

#include "engine_pch.h"
#include "core/inputPoller.h"

#ifdef NG_PLATFORM_WINDOWS
#include "platform/GLFW/GLFWInputPoller.h"

namespace Engine
{
	bool InputPoller::isKeyPressed(int32_t keyCode)
	{
		return GLFWInputPoller::isKeyPressed(keyCode); //!< Pass the call to the GLFW inputPoller
	}
	bool InputPoller::isMouseButtonPressed(int32_t mouseButton)
	{
		return GLFWInputPoller::isMouseButtonPressed(mouseButton); //!< Pass the call to the GLFW inputPoller
	}
	glm::vec2 InputPoller::getMousePosition() 
	{
		return GLFWInputPoller::getMousePosition(); //!< Pass the call to the GLFW inputPoller
	}
	void InputPoller::setNativeWindow(void * nativeWin) 
	{
		GLFWInputPoller::setCurrentWindow(reinterpret_cast<GLFWwindow*>(nativeWin)); //!< Pass the call to the GLFW inputPoller
	} 
}
#endif