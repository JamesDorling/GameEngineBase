/*! \file GLFW_OpenGL_GC.h */
#pragma once

#include "core/graphicsContext.h"

namespace Engine
{
	class GLFW_OpenGL_GC : public GraphicsContext
	{
	public:
		GLFW_OpenGL_GC(GLFWwindow * window) : m_window(window) {} //!< Constructor, assigns the window
		virtual void init() override; //!< Init the current window API's graphics context
		virtual void swapBuffers() override; //!< Swap the front and back buffers
	private:
		GLFWwindow * m_window; //!< Window
	};
}