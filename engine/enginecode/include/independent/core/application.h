/*! \file application.h
*/
#pragma once

#include "systems/log.h"
#include "timer.h"
#include "events/events.h"
#include "core/window.h"
#include "inputPoller.h"

namespace Engine {

	/*!
	\class Application
	Fundemental class of the engine. A singleton which runs the game loop infinitely.
	Provides ...
	*/

	class Application
	{
	protected:
		Application(); //!< Constructor

		std::shared_ptr<Log> m_logSystem; //!< Console Logger
		std::shared_ptr<System> m_windowsSystem; //!< Windows system

		//Non systems
		std::shared_ptr<ChronoTimer> m_timer; //!< Timer
		std::shared_ptr<Window> m_window; //!< Window
		EventHandler m_handler; //!< Event handler

		//Window Events
		bool onClose(WindowCloseEvent& i); //!< Runs when the window is closed
		bool onResize(WindowResizeEvent& i); //!< Runs when the window is resized
		bool onWinMove(WindowMoved& i); //!< Runs when window is moved
		bool onLostFocus(WindowLostFocus& i); //!< Runs when window loses focus
		bool onFocus(WindowFocus& i); //!< Runs when window gains focus

		//Keyboard Events
		bool onKeyPressed(KeyPressed& i);//!< Called whenever a key is pressed
		bool onKeyReleased(KeyReleased& i); //!< Called whenever a key is released
		bool onKeyTyped(KeyTyped& i); //!< Called when a key is pressed in the context of typing

		//Mouse Events
		bool onMouseButtonPressed(MouseButtonPressed& i); //!< Called when a mouse button is pressed
		bool onMouseButtonReleased(MouseButtonReleased& i); //!< Called when a mouse button is released
		bool onMouseMoved(MouseMoved& i); //!< Called whenever the mouse is moved
		bool onMouseScrolled(MouseScrolled& i); //!< Called whenever the mouse is scrolled, whether it be the scroll wheel or the 




	private:
		static Application* s_instance; //!< Singleton instance of the application
		bool m_running = true; //!< Is the application running?
	public:
		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; } //!< Instance getter from singleton pattern
		inline std::shared_ptr<Window> getWindow() { return m_window; } //!< Getter for the window (Used in win32)
		void run(); //!< Main loop
	};

	// To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook
}