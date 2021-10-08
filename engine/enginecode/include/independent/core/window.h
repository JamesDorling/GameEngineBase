/*! \file window.h */
#pragma once

#include "events/eventHandler.h"
#include "graphicsContext.h"

namespace Engine
{
	/*! \struct WindowProperties
	* \brief Abstract windows base class. All implemented windows should code to this interface.
	*/
	struct WindowProperties
	{
		char * title; //!< Window title
		uint32_t width; //!< Width of the window
		uint32_t height; //!< Height of the window
		bool isFullScreen; //!< Boolean if the window is fullscreen
		bool isVSync; //!< boolean if VSync is on

		WindowProperties(char * title = "My Window", unsigned int width = 800, unsigned int height = 600, bool fullscreen = false) : title(title), width(width), height(height), isFullScreen(fullscreen) {}
	};
	/* \class Window
	* \brief window base class
	*/
	class Window
	{
	public:
		virtual void init(const WindowProperties& properties) = 0; //!< Initialise the window
		virtual void close() = 0; //!< close window
		virtual ~Window() {} //!< Deconstructor
		virtual void onUpdate(float timestep) = 0; //!< Update each frame
		virtual void setVSync(bool VSync) = 0; //!< Set VSync
		virtual inline uint32_t getWidth() const = 0; //!< Get width of window
		virtual inline uint32_t getHeight() const = 0; //!< Get height of window
		virtual void* getNativeWindow() const = 0; //!< Get native window
		virtual bool isFullScreenMode() const = 0; //!< Set if fullscreen
		virtual bool isVSync() const = 0; //!< Set if VSync


		inline EventHandler& getEventHandler() { return m_handler; } //!< Getter for the handler

		static Window* create(const WindowProperties& properties = WindowProperties()); //!< Create the window
	protected:
		std::shared_ptr<GraphicsContext> m_graphicsContext;
		EventHandler m_handler; //!< Event handler
	};
}