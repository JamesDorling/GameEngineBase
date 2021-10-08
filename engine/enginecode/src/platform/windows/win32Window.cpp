/* \file win32Window.cpp */

#include "engine_pch.h"
#include "platform/windows/win32Window.h"
#include "platform/windows/win32_OpenGL_GC.h"
#include "systems/log.h"

namespace Engine
{

	void Win32Window::init(const WindowProperties & properties)
	{
		wchar_t wStr[256];
		mbstowcs(wStr, properties.title, 256);
		//LPCWSTR title = L"Title";
		int32_t x;
		int32_t y;
		if (properties.isFullScreen)
		{
			x = 0;
			y = 0;
		}
		else
		{
			x = GetSystemMetrics(SM_CXSCREEN) / 2 - properties.width / 2;
			y = GetSystemMetrics(SM_CYSCREEN) / 2 - properties.height / 2;
		}

		m_native = CreateWindow(L"NGWin32Window", wStr, WS_OVERLAPPEDWINDOW, x, y, properties.width, properties.height, NULL, NULL, GetModuleHandle(NULL), NULL);

		if (!m_native)
		{
			Log::error("Failed to create Win32 window");
		}

		//GC
		m_graphicsContext.reset(new Win32_OpenGL_GC(m_native));

		ShowWindow(m_native, SW_SHOW);
	}

	void Win32Window::close()
	{
		DestroyWindow(m_native);
	}

	void Win32Window::onUpdate(float timestep)
	{
		MSG msg = {};
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		m_graphicsContext->swapBuffers();
	}
	LRESULT Win32Window::onWin32Msg(HWND hWin, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_DESTROY:
		{
			WindowCloseEvent i;
			auto& onClose = m_handler.getOnCloseCallback();
			onClose(i);
			break;
		}
		case WM_SIZE :
		{
			int32_t width = LOWORD(lParam);
			int32_t height = HIWORD(lParam);

			WindowResizeEvent i(width, height);
			auto& onResize = m_handler.getOnResizeCallback();
			onResize(i);
			break;
		}


		case WM_KEYDOWN:
		{
			int32_t keycode = static_cast<int32_t>(wParam);
			int32_t repeat = LOWORD(lParam);
			KeyPressed i(keycode, repeat);
			auto& onKeyPressed = m_handler.getOnKeyPressed();
			onKeyPressed(i);
			break;
		}
		default:
			return DefWindowProc(hWin, msg, wParam, lParam);
			break;
		}
		return 0;
	}
}