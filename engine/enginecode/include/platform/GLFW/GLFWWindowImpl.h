/*! \file GLFWWindowImpl.h */
#pragma once

#include "core/window.h"
#include <GLFW/glfw3.h>

namespace Engine 
{
	/*! \class GLFWWindowImpl
	* \brief Implementation of a GLFW window
	*/
	class GLFWWindowImpl : public Window
	{
	public:
		GLFWWindowImpl(const WindowProperties& properties); //!< Constructor
		virtual void init(const WindowProperties& properties) override; //!< Initialise the GLFW window
		virtual void close() override; //!< Close, called when the window closes
		virtual ~GLFWWindowImpl() {} //!< Deconstructor
		virtual void onUpdate(float timestep) override; //!< Update, called every frame
		virtual void setVSync(bool VSync) override; //!< Setter for VSync
		virtual inline uint32_t getWidth() const override { return m_properties.width; } //!< Getter for the width
		virtual inline uint32_t getHeight() const override { return m_properties.height; } //!< Getter for the height
		virtual inline void* getNativeWindow() const override { return m_native; } //!< Getter for the window
		virtual inline bool isFullScreenMode() const override { return m_properties.isFullScreen; } //!< Getter for the boolean of if the screen is fullscreen
		virtual inline bool isVSync() const override { return m_properties.isVSync; } //!< Getter for if VSync is on

	private:
		WindowProperties m_properties; //!< Properties
		GLFWwindow * m_native; //!< Native GLFW Window
		float m_aspectRatio; //!< Aspect Ratio
	};

}
