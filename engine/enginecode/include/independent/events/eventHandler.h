/*! \file eventHandler.h */
#pragma once

#include "events.h"
#include <functional>



namespace Engine
{
	/*! \class EventHandler
	* Event handler base class, handles setting callback functions on events.
	*/
	class EventHandler
	{
	public:
		void setOnCloseCallback(const std::function<bool(WindowCloseEvent&)>& fn) { m_onCloseFunction = fn; } //!< Setters for the callbacks
		void setOnResizeCallback(const std::function<bool(WindowResizeEvent&)>& fn) { m_onResizeFunction = fn; }
		void setOnFocusCallback(const std::function<bool(WindowFocus&)>& fn) { m_onFocused = fn; }
		void setOnLostFocusCallback(const std::function<bool(WindowLostFocus&)>& fn) { m_onFocusLost = fn; }
		void setOnMovedWinCallback(const std::function<bool(WindowMoved&)>& fn) { m_onMoveFunction = fn; }
		void setOnKeyPressedCallback(const std::function<bool(KeyPressed&)>& fn) { m_onKeyPressed = fn; }
		void setOnKeyReleasedCallback(const std::function<bool(KeyReleased&)>& fn) { m_onKeyReleased = fn; }
		void setOnKeyTypedCallback(const std::function<bool(KeyTyped&)>& fn) { m_onKeyTyped = fn; }
		void setOnMousePressedCallback(const std::function<bool(MouseButtonPressed&)>& fn) { m_onMousePressed = fn; }
		void setOnMouseReleasedCallback(const std::function<bool(MouseButtonReleased&)>& fn) { m_onMouseReleased = fn; }
		void setOnMouseMovedCallback(const std::function<bool(MouseMoved&)>& fn) { m_onMouseMoved = fn; }
		void setOnMouseScrolledCallback(const std::function<bool(MouseScrolled&)>& fn) { m_onMouseScrolled = fn; }

		std::function<bool(WindowCloseEvent&)> getOnCloseCallback() { return m_onCloseFunction; }; //!< Accessors to pass reference
		std::function<bool(WindowResizeEvent&)> getOnResizeCallback() { return m_onResizeFunction; }; 
		std::function<bool(WindowFocus&)> getOnFocused() { return m_onFocused; };
		std::function<bool(WindowLostFocus&)> getOnFocusLost() { return m_onFocusLost; };
		std::function<bool(WindowMoved&)> getOnMoveFunction() { return m_onMoveFunction; };
		std::function<bool(KeyPressed&)> getOnKeyPressed() { return m_onKeyPressed; };
		std::function<bool(KeyReleased&)> getOnKeyReleased() { return m_onKeyReleased; }; 
		std::function<bool(KeyTyped&)> getOnKeyTyped() { return m_onKeyTyped; }; 
		std::function<bool(MouseButtonPressed&)> getOnMousePressed() { return m_onMousePressed; }; 
		std::function<bool(MouseButtonReleased&)> getOnMouseReleased() { return m_onMouseReleased; };
		std::function<bool(MouseMoved&)> getOnMouseMoved() { return m_onMouseMoved; };
		std::function<bool(MouseScrolled&)> getOnMouseScrolled() { return m_onMouseScrolled; }; 
	private:
		std::function<bool(WindowCloseEvent&)> m_onCloseFunction = std::bind(&EventHandler::defaultOnClose, this, std::placeholders::_1);//!< Binding a standard function to a parameter to take an input and be callable
		std::function<bool(WindowResizeEvent&)> m_onResizeFunction = std::bind(&EventHandler::defaultOnResize, this, std::placeholders::_1);
		std::function<bool(WindowFocus&)> m_onFocused = std::bind(&EventHandler::defaultOnFocus, this, std::placeholders::_1);
		std::function<bool(WindowLostFocus&)> m_onFocusLost = std::bind(&EventHandler::defaultOnFocusLost, this, std::placeholders::_1);
		std::function<bool(WindowMoved&)> m_onMoveFunction = std::bind(&EventHandler::defaultOnMovedWin, this, std::placeholders::_1);
		std::function<bool(KeyPressed&)> m_onKeyPressed = std::bind(&EventHandler::defaultOnKeyPressed, this, std::placeholders::_1);
		std::function<bool(KeyReleased&)> m_onKeyReleased = std::bind(&EventHandler::defaultOnKeyReleased, this, std::placeholders::_1);
		std::function<bool(KeyTyped&)> m_onKeyTyped = std::bind(&EventHandler::defaultOnKeyTyped, this, std::placeholders::_1);
		std::function<bool(MouseButtonPressed&)> m_onMousePressed = std::bind(&EventHandler::defaultOnMBPressed, this, std::placeholders::_1);
		std::function<bool(MouseButtonReleased&)> m_onMouseReleased = std::bind(&EventHandler::defaultOnMBReleased, this, std::placeholders::_1);
		std::function<bool(MouseMoved&)> m_onMouseMoved = std::bind(&EventHandler::defaultOnMouseMoved, this, std::placeholders::_1);
		std::function<bool(MouseScrolled&)> m_onMouseScrolled = std::bind(&EventHandler::defaultOnMouseScrolled, this, std::placeholders::_1);

		bool defaultOnClose(WindowCloseEvent& i) { return false; }; //!< Return false by default, as we by default havent handled a function
		bool defaultOnResize(WindowResizeEvent& i) { return false; };
		bool defaultOnFocus(WindowFocus& i) { return false; };
		bool defaultOnFocusLost(WindowLostFocus& i) { return false; };
		bool defaultOnMovedWin(WindowMoved& i) { return false; };
		bool defaultOnKeyPressed(KeyPressed& i) { return false; };
		bool defaultOnKeyReleased(KeyReleased& i) { return false; };
		bool defaultOnKeyTyped(KeyTyped& i) { return false; };
		bool defaultOnMBPressed(MouseButtonPressed& i) { return false; };
		bool defaultOnMBReleased(MouseButtonReleased& i) { return false; };
		bool defaultOnMouseMoved(MouseMoved& i) { return false; };
		bool defaultOnMouseScrolled(MouseScrolled& i) { return false; };
	};
}