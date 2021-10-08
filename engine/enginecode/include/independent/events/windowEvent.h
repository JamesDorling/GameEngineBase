/*! \file windowEvent.h */
#pragma once

#include "event.h"
#include <glm/glm.hpp>

namespace Engine
{
	/*! \class WindowCloseEvent
	* /brief Handler for the windowcloseevent event
	* Event is called when the window is closed
	*/
	class WindowCloseEvent : public Event
	{
	public:
		static EventType getStaticType() { return EventType::WindowClose; } //!< Return static type
		virtual inline EventType getEventType() const override { return EventType::WindowClose; }; //!< Get the event type
		virtual int32_t getCategoryFlag() const override { return EventCategoryWindow; }; //!< Get the category flag
	};

	/*! \class WindowResizeEvent
	* /brief Handler for the  windowresizeevent event
	* Event is called when the window is resized
	*/
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int32_t width, int32_t height) : m_width(width), m_height(height) {} //!< Constructor, assigns the width and height
		static EventType getStaticType() { return EventType::WindowResize; } //!< Return static type
		virtual inline EventType getEventType() const override { return EventType::WindowResize; }; //!< Get the event type
		virtual int32_t getCategoryFlag() const override { return EventCategoryWindow; }; //!< Get the category flag
		inline int32_t getWidth() const { return m_width; } //!< Getter for the width
		inline int32_t getHeight() const { return m_height; } //!< Getter for the height
		inline glm::ivec2 getSize() const { return { m_width, m_height }; } //!< Getter for the size in an ivec2
	private:
		int32_t m_width;	//!< Width of the window after resize
		int32_t m_height;	//!< height of the window after resize
	};

	/*! \class WindowFocus
	* /brief Handler for the windowfocus event
	* Event is called when the window gains focus
	*/
	class WindowFocus : public Event
	{
	public:
		static EventType getStaticType() { return EventType::WindowFocus; } //!< Return static type
		virtual inline EventType getEventType() const override { return EventType::WindowFocus; }; //!< Get the event type
		virtual int32_t getCategoryFlag() const override { return EventCategoryWindow; }; //!< Get the category flag
	};

	/*! \class WindowLostFocus
	* \brief Handler for the windowlostfocus event
	* Event is called when the window loses focus
	*/ 
	class WindowLostFocus : public Event
	{
	public:
		static EventType getStaticType() { return EventType::WindowLostFocus; } //!< Return static type
		virtual inline EventType getEventType() const override { return EventType::WindowLostFocus; }; //!< Get the event type
		virtual int32_t getCategoryFlag() const override { return EventCategoryWindow; }; //!< Get the category flag
	};

	/*! \class WindowMoved
	* /brief Handler for the windowmoved event
	* Event is called when the window is moved
	*/
	class WindowMoved : public Event
	{
	public:
		WindowMoved(int32_t X, int32_t Y) : m_Xpos(X), m_Ypos(Y) {} //!< Constructors, assigns the position of the window to the int variables
		static EventType getStaticType() { return EventType::WindowMoved; } //!< Return static type
		virtual inline EventType getEventType() const override { return EventType::WindowMoved; }; //!< Get the event type
		virtual int32_t getCategoryFlag() const override { return EventCategoryWindow; }; //!< Get the category flag

		inline int32_t getX() const { return m_Xpos; } //!< Getter for the x coordinate
		inline int32_t getY() const { return m_Ypos; } //!< Getter for the y coordinate
		inline glm::ivec2 getPos() const { return { m_Xpos, m_Ypos }; } //!< Getter for the window position in a vec2
	private:
		int32_t m_Xpos, m_Ypos;	//!< Width and height of the window after resize
		
	};
}
