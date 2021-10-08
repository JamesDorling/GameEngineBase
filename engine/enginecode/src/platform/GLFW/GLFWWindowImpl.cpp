/*! \file GLFWWindowImpl.cpp 
*/
#include "engine_pch.h"
#include "platform/GLFW/GLFWWindowImpl.h"
#include "platform/GLFW/GLFW_OpenGL_GC.h"
#include "systems/log.h"

namespace Engine 
{
	GLFWWindowImpl::GLFWWindowImpl(const WindowProperties & properties)
	{
		init(properties); //!< Initialise the window with the properties in the constructor
	}

	void GLFWWindowImpl::init(const WindowProperties & properties)
	{
		m_properties = properties; //!< Keep a copy of the properties
		m_aspectRatio = static_cast<float>(m_properties.width / m_properties.height); //!< Set the aspect ratio

		if (m_properties.isFullScreen)
		{
			m_native = glfwCreateWindow(m_properties.width, m_properties.height, m_properties.title, glfwGetPrimaryMonitor(), nullptr); //!< If the screen should be full screen create it to be full screen
		}
		else
		{
			m_native = glfwCreateWindow(m_properties.width, m_properties.height, m_properties.title, nullptr, nullptr); //!< If full screen is off create the window normally
		}

		m_graphicsContext.reset(new GLFW_OpenGL_GC(m_native)); //!< Reset the graphics context pointer
		m_graphicsContext->init(); //!< Initialise the graphics context

		glfwSetWindowUserPointer(m_native, static_cast<void*>(&m_handler)); //!< Set the window's user pointer to the handler

		//Window Events

		glfwSetWindowCloseCallback(m_native,
			[](GLFWwindow * window)
		{
			EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
			auto& onClose = handler->getOnCloseCallback();

			WindowCloseEvent i;
			onClose(i);
		}); //!< Set the close event callback

		glfwSetWindowSizeCallback(m_native,
			[](GLFWwindow * window, int32_t newWidth, int32_t newHeight)
		{
			EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
			auto& onResize = handler->getOnResizeCallback();

			WindowResizeEvent i(newWidth, newHeight);
			onResize(i);
		}); //!< Set the window resize event callback

		glfwSetWindowPosCallback(m_native,
			[](GLFWwindow * window, int32_t newTopL, int32_t newBottomR)
		{
			EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
			auto& onWinMove = handler->getOnMoveFunction();

			WindowMoved i(newTopL, newBottomR);
			onWinMove(i);
		});  //!< Set the window moved event callback

		glfwSetWindowFocusCallback(m_native,
			[](GLFWwindow * window, int32_t focused)
		{
			EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
			//Log::info("Focus value: {0}", focused);
			if (focused == GLFW_TRUE)
			{
				auto& onFocus = handler->getOnFocused();
				WindowFocus i;
				onFocus(i);

			}
			else if (focused == GLFW_FALSE)
			{
				auto& onLostFocus = handler->getOnFocusLost();
				WindowLostFocus i;
				onLostFocus(i);
			}
		});  //!< Set both the window lost focus event and the window gained focus event callbacks

		//Keyboard Events

		glfwSetKeyCallback(m_native,
			[](GLFWwindow * window, int32_t keycode, int32_t scancode, int32_t action, int32_t mods)
		{
			EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));

			if (action == GLFW_PRESS)
			{
				auto& onKeyPress = handler->getOnKeyPressed();
				KeyPressed i(keycode, 0);
				onKeyPress(i);
			}
			else if (action == GLFW_REPEAT)
			{
				auto& onKeyPress = handler->getOnKeyPressed();
				KeyPressed i(keycode, 1);
				onKeyPress(i);
			}
			else if (action == GLFW_RELEASE)
			{
				auto& onKeyRelease = handler->getOnKeyReleased();
				KeyReleased i(keycode);
				onKeyRelease(i);
			}
		});  //!< Set the key event callbacks

		glfwSetCharCallback(m_native,
			[](GLFWwindow * window, uint32_t keycode)
		{
			EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
			auto& onKeyTyped = handler->getOnKeyTyped();
			KeyTyped i(keycode);
			onKeyTyped(i);
		}); //!< Set the on key typed event callback

			//Mouse Events

		glfwSetMouseButtonCallback(m_native,
			[](GLFWwindow * window, int32_t button, int32_t action, int32_t mods)
		{
			EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));

			if (action == GLFW_PRESS)
			{
				auto& onMouseButtonPressed = handler->getOnMousePressed();
				MouseButtonPressed i(button);
				onMouseButtonPressed(i);
			}
			else if (action == GLFW_RELEASE)
			{
				auto& onMouseButtonReleased = handler->getOnMouseReleased();
				MouseButtonReleased i(button);
				onMouseButtonReleased(i);
			}
		}); //!< Set the mouse button callbacks

		glfwSetCursorPosCallback(m_native,
			[](GLFWwindow * window, double xPos, double yPos)
		{
			EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
			auto& onMouseMoved = handler->getOnMouseMoved();
			MouseMoved i(xPos, yPos);
			onMouseMoved(i);
		}); //!< Set the mouse moved callback

		glfwSetScrollCallback(m_native,
			[](GLFWwindow * window, double xOffset, double yOffset)
		{
			EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
			auto& onMouseScrolled = handler->getOnMouseScrolled();
			MouseScrolled i(xOffset, yOffset);
			onMouseScrolled(i);
		}); //!< Set the scroll event callback
	}

	void GLFWWindowImpl::close()
	{
		glfwDestroyWindow(m_native); //!< Delete the window
	}

	void GLFWWindowImpl::onUpdate(float timestep)
	{
		glfwPollEvents(); //!< Check for events
		m_graphicsContext->swapBuffers(); //!< Swap the buffers
	}

	void GLFWWindowImpl::setVSync(bool VSync)
	{
		m_properties.isVSync = VSync;
		if (VSync) 
		{
			glfwSwapInterval(1); //!< If VSync should be on, use VSync
		}
		else
		{ 
			glfwSwapInterval(0); //!< If VSync should be off, dont use VSync
		}
	}
}