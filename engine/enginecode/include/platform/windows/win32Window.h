/*! \file win32Window.h */
#pragma once

#include "core/window.h"

//Targetting windows 10
#define WINVER 0x0A00
#define _WIN32_WINNT 0X0A00

#include <windows.h>
#include <tchar.h>

namespace Engine
{
	class Win32Window : public Window
	{
	public:
		Win32Window(const WindowProperties& properties) { init(properties); } //!< Constructor. passes properties to init.
		virtual void init(const WindowProperties& properties) override; //!< Initialises the window
		virtual void close() override; //!< Called when the window is closing.
		virtual ~Win32Window() {} //!< Destructor
		virtual void onUpdate(float timestep) override; //!< Onupdate, called every frame.
		virtual void setVSync(bool VSync)  override {} //!< Setter for VSync
		virtual inline uint32_t getWidth() const override { return m_properties.width; } //!< Getter for the width of the window
		virtual inline uint32_t getHeight() const override { return m_properties.height; }  //!< Getter for the height of the window
		virtual inline void* getNativeWindow() const override { return m_native; }  //!< Getter for the native window
		virtual inline bool isFullScreenMode() const  override { return m_properties.isFullScreen; }  //!< Getter for whether the window is fullscreen
		virtual inline bool isVSync() const override { return false; }  //!< Getter for whether VSync is on (Off because not implemented)
		LRESULT CALLBACK onWin32Msg(HWND hWin, UINT msg, WPARAM wParam, LPARAM lParam); //!< Windows pipeline, not fully implemented

	private:
		HWND m_native; //!< Native win32 window
		WindowProperties m_properties; //!< Properties
		float m_aspectRatio; //!< Aspect Ratio
	};
}