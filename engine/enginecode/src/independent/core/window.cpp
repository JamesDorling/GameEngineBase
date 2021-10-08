/*! \file window.cpp */

#include "engine_pch.h"
#include "core/window.h"
#include "platform/GLFW/GLFWWindowImpl.h"
#include "platform/windows/win32Window.h"

namespace Engine
{
#ifdef NG_PLATFORM_WINDOWS
//	Window* Window::create(const WindowProperties& properties)
//	{
//		return new Win32Window(properties);
//	}
//#else
	Window* Window::create(const WindowProperties& properties)
	{
		return new GLFWWindowImpl(properties); //!< Pass the window properties to GLFWWindowImpl to render a GLFW window
	}
#endif
}