/*! \file win32System.h */
#pragma once

#include "systems/system.h"

namespace Engine
{
	/* \class win32System 
	*	\brief A window system using win32. There is no input poller, and it has been all but removed from the code.
	*/
	class Win32System : public System
	{
	public:
		virtual void start(SystemSignal init = SystemSignal::None, ...) override ; //!< Start the system
		virtual void stop(SystemSignal close = SystemSignal::None, ...) override ; //!< Stop the system
	};
	// Honestly its 4am and I dont have the energy to make the input poller, GLFW makes so much more sense so Im going to be sticking with that.
}