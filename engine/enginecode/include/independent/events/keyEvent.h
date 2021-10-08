/*! \file keyEvent.h */
#pragma once

#include "event.h"
#include <glm/glm.hpp>

namespace Engine
{
	/*! \class KeyEvent
	* /brief Base class for keyboard-based events.
	*/
	class KeyEvent : public Event
	{
	protected:
		KeyEvent(int32_t keyCode) : m_keyCode(keyCode) {} //!< Constructor
		int32_t m_keyCode; //!< Keycode
	public:
		inline int32_t getKeyCode() const { return m_keyCode; } //!< Getter for the keycode
		virtual inline int32_t getCategoryFlag() const override { return EventCategoryKeyboard | EventCategoryInput; } //!< getter for the category flag
	};

	/*! \class KeyPressed
	* /brief Handles the keypressed event
	* Event is called whenever a key is pressed
	*/
	class KeyPressed : public KeyEvent
	{
	public:
		KeyPressed(int32_t key, bool repeat) : KeyEvent(key), m_repeatCount(repeat) {} //!< Constructor
		static EventType getStaticType() { return EventType::KeyPressed; } //!< Return static type
		virtual inline EventType getEventType() const override { return EventType::KeyPressed; }; //!< Get the event type
		inline int32_t getRepeatCount() const { return m_repeatCount; }; //!< Getter for the repeat count
	private:
		bool m_repeatCount;
	};

	/*! \class KeyReleased
	* /brief Handles the keyreleased event
	* Event is called whenever a key is released
	*/
	class KeyReleased : public KeyEvent
	{
	public:
		KeyReleased(int32_t key) : KeyEvent(key) {}
		static EventType getStaticType() { return EventType::KeyReleased; } //!< Return static type
		virtual inline EventType getEventType() const override { return EventType::KeyReleased; }; //!< Get the event type
		int32_t KeyCode; //!< Keycode
	};

	/*! \class KeyTyped
	* /brief Handles the keytyped event
	* Event is called whenever a key is pressed in a typing context for example a text box
	*/
	class KeyTyped : public KeyEvent
	{
	public:
		KeyTyped(int32_t key) : KeyEvent(key) {} //!< Constructor, assigns the keyevent keycode
		static EventType getStaticType() { return EventType::KeyTyped; } //!< Return static type
		virtual inline EventType getEventType() const override { return EventType::KeyTyped; }; //!< Get the event type
		int32_t KeyCode; //!< Keycode
	};
}
