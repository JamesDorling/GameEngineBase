/*! \file mouseEvent.h */
#pragma once


#include "event.h"
#include <glm/glm.hpp>

namespace Engine
{
	/*! \class MouseButtonEvent
	* /brief Base class for mouse events that use a button
	*/
	class MouseButtonEvent : public Event
	{
	protected:
		MouseButtonEvent(int32_t mouseButton) : m_mouseButton(mouseButton) {} //!< Constructor, assigns mouseButton
		int32_t m_mouseButton; //!< Mouse Button
	public:
		inline int32_t getMouseButton() const { return m_mouseButton; } //!< Getter for the mousebutton
		virtual inline int32_t getCategoryFlag() const override { return EventCategoryMouse | EventCategoryInput; }
	};

	/*! \class MouseButtonPressed
	* /brief Handles the mousebuttonpressed event
	* Event is called whenever a mouse button is initially pressed down
	*/
	class MouseButtonPressed : public MouseButtonEvent
	{
	public:
		MouseButtonPressed(int32_t mouseButton) : MouseButtonEvent(mouseButton) {} //!< Constructor, assigns mouseButton
		static EventType getStaticType() { return EventType::MouseButtonPressed; } //!< Return static type
		virtual inline EventType getEventType() const override { return EventType::MouseButtonPressed; }; //!< Get the event type
	private:
		int32_t m_mouseButton; //!< Mouse button
	};

	/*! \class MouseButtonReleased
	* /brief Handles the mousebuttonreleased event
	* Event is called whenevet a mouse button is released
	*/
	class MouseButtonReleased : public MouseButtonEvent
	{
	public:
		MouseButtonReleased(int32_t mouseButton) : MouseButtonEvent(mouseButton) {} //!< Constructor, assigns mouseButton
		static EventType getStaticType() { return EventType::MouseButtonReleased; } //!< Return static type
		virtual inline EventType getEventType() const override { return EventType::MouseButtonReleased; }; //!< Get the event type
	private:
		int32_t m_mouseButton; //!< Mouse button
	};

	/*! \class MouseMoved
	* /brief Handler for the mousemoved event
	* Event is called whenever the mouse is moved
	*/
	class MouseMoved : public Event
	{
	public:
		MouseMoved(float X, float Y) : m_Xpos(X), m_Ypos(Y) {} //!< Constructor, assigns the position
		static EventType getStaticType() { return EventType::MouseMoved; } //!< Return static type
		virtual inline EventType getEventType() const override { return EventType::MouseMoved; }; //!< Get the event type
		virtual int32_t getCategoryFlag() const override { return EventCategoryMouse | EventCategoryInput; }; //!< Get the category flag
		inline float getX() const { return m_Xpos; } //!< Getter for the X coordinate
		inline float getY() const { return m_Ypos; } //!< Getter for the Y coordinate
		inline glm::vec2 getPos() const { return glm::vec2(m_Xpos, m_Ypos); } //!< Getter for the coordinates in a vec2 format
	private:
		float m_Xpos, m_Ypos;	//!< Pos of the mouse on x and y
	};

	/*! \class MouseScrolled
	* /brief Handler for the mousescrolled event
	* Event is called whenever the user scrolls, be it with a scroll wheel or a trackball
	*/
	class MouseScrolled : public Event
	{
	public:
		MouseScrolled(double m_xPos, double m_yPos) : m_Xpos(m_xPos), m_Ypos(m_yPos) {} //!< Constructor
		static EventType getStaticType() { return EventType::MouseScrolled; } //!< Return static type
		virtual inline EventType getEventType() const override { return EventType::MouseScrolled; }; //!< Get the event type
		virtual int32_t getCategoryFlag() const override { return EventCategoryMouse | EventCategoryInput; }; //!< Get the category flag
		inline double getX() const { return m_Xpos; } //!< Getter for the X coordinate
		inline double getY() const { return m_Ypos; } //!< Getter for the Y coordinate
	private:
		double m_Xpos;	//!< Width of the window after resize
		double m_Ypos;	//!< height of the window after resize
	};
}