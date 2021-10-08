/* \file win32_OpenGL_GC.cpp */

#include "engine_pch.h"
#include "platform/windows/win32_OpenGL_GC.h"
#include "systems/log.h"

#include <glad/glad.h>

namespace Engine
{

	Win32_OpenGL_GC::~Win32_OpenGL_GC()
	{
		wglMakeCurrent(0, 0);
		wglDeleteContext(m_context);
		ReleaseDC(m_window, m_deviceContext);
	}

	void Win32_OpenGL_GC::init()
	{
		m_deviceContext = GetDC(m_window);

		PIXELFORMATDESCRIPTOR pfd;

		memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 24;
		pfd.cStencilBits = 8;

		int format = ChoosePixelFormat(m_deviceContext, &pfd);
		if (!SetPixelFormat(m_deviceContext, format, &pfd))
		{
			Log::error("Could not set pixel format for win32 window");
		}

		m_context = wglCreateContext(m_deviceContext);
		if (!wglMakeCurrent(m_deviceContext, m_context))
		{
			Log::error("Could not set wgl context to current");
		}

		if (!wglGetCurrentContext())
		{
			Log::error("No valid openGL context");
		}

		if (!gladLoadGL())
		{
			Log::error("Failed to load glad");
		}
	}

	void Win32_OpenGL_GC::swapBuffers()
	{
		SwapBuffers(m_deviceContext);
	}
}
