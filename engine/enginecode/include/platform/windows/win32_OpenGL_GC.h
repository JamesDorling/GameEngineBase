/* \file win32_OpenGL_GC.h */
#pragma once

#include "core/graphicsContext.h"

//Targetting windows 10
#define WINVER 0x0A00
#define _WIN32_WINNT 0X0A00

#include <Windows.h>

namespace Engine
{
	/*!
	\class Win32_OpenGL_GC
	\brief win32 graphics context using openGL
	*/
	class Win32_OpenGL_GC : public GraphicsContext
	{
	public:
		Win32_OpenGL_GC(HWND hWin) : m_window(hWin) { init(); } //!< constructor, calls init
		~Win32_OpenGL_GC(); //!< Destructor
		virtual void init() override; //!< Init the current window API's graphics context
		virtual void swapBuffers() override; //!< Swap the front and back buffers
	private:
		HWND m_window = nullptr; //!< Current window handle
		HDC m_deviceContext = nullptr; //!< Device context handle
		HGLRC m_context = nullptr; //!< OpenGL context handle
	};
}