/*! \file renderCommands.h */
#pragma once

#include <functional>

namespace Engine
{
	class RenderCommand
	{
	public:
		virtual void action() = 0;
		
		static RenderCommand * clearDepthColourCommand(); //!< clearing the depth and the colour buffer. We do this enough to warrant them both having a shared command.
		static RenderCommand * setClearColourCommand(float r, float g, float b, float a); //!< set the background colour
		static RenderCommand * setDepthTestCommand(bool enabled); //!< Enable / disable depth testing
		static RenderCommand * setBackfaceCullingCommand(bool enabled); //!< Enable / disable backface culling
		static RenderCommand * setBlendCommand(bool enabled); //!< Enable / disable blending

	};
}
