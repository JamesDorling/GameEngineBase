/*! \file inputPoller.h 
*/
#pragma once

#include <glm/glm.hpp>

namespace Engine
{
	/* \class InputPoller
	*	/brief API agnostic input poller for getting current keyboard/mouse states
	*/
	class InputPoller
	{
	public:
		static bool isKeyPressed(int32_t keyCode); //!< Is a key pressed
		static bool isMouseButtonPressed(int32_t mouseButton); //!< Is a mouse button pressed
		static glm::vec2 getMousePosition(); //!< Current mouse pos
		static void setNativeWindow(void* nativeWin); //!< Setter for the native window
		inline static float getMouseX() { return getMousePosition().x; } //!< Getter for the mouse position on the X axis
		inline static float getMouseY() { return getMousePosition().y; } //!< Getter for the mouse position on the Y axis
	};
}
