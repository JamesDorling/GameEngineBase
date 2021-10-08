/*! \file graphicsContext.h */
#pragma once

namespace Engine
{
	class GraphicsContext
	{
		/*! \class GraphicsContext
		* /brief This class is the base class for graphics contexts.
		*/
	public:
		virtual void init() = 0; //!< Init the current window API's graphics context
		virtual void swapBuffers() = 0; //!< Swap the front and back buffers
	};
}