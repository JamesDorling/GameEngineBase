/*! \file OpenGLRenderCommands.h */
#pragma once

#include "renderCommands.h"

namespace Engine
{
	/*! \class ClearDepthColourCommand
	\brief Render command for clearing the depth buffer and the colour buffer
	*/
	class OpenGLClearDepthColourCommand : public RenderCommand
	{
	public:
		OpenGLClearDepthColourCommand() {}; //!< Constructor
		void action() override; //!< Action
	};

	/*! \class ClearDepthBufferCommand
	\brief Render command for clearing the depth buffer
	*/
	class OpenGLClearDepthBufferCommand : public RenderCommand
	{
	public:
		OpenGLClearDepthBufferCommand() {}; //!< Constructor
		void action() override; //!< Action
	};

	/*! \class Set Depth Test Command
	\brief Render command for setting depth testing
	*/
	class OpenGLSetDepthTestCommand : public RenderCommand
	{
	private:
		bool m_enabled; //!< Enabled boolean
	public:
		OpenGLSetDepthTestCommand(bool enabled) : m_enabled(enabled) {};  //!< Constructor, takes a boolean
		void action() override; //!< Action
	};

	/*! \class Set Clear Colour Command
	\brief Render command for setting depth testing
	*/
	class OpenGLSetClearColourCommand : public RenderCommand
	{			   
	private:
		float m_r, m_g, m_b, m_a; //!< The RGBA values
	public:		   
		OpenGLSetClearColourCommand(float r, float g, float b, float a) : m_r(r), m_g(g), m_b(b), m_a(a) {};  //!< Constructor, takes a boolean
		void action() override; //!< Action
	};

	/*! \class OpenGLSetBackfaceCullingCommand
	\brief Render command for setting the backface culling
	*/
	class OpenGLSetBackfaceCullingCommand : public RenderCommand
	{
	private:
		bool m_enabled; //!< Enabled boolean
	public:
		OpenGLSetBackfaceCullingCommand(bool enabled) : m_enabled(enabled) {}; //!< Constructor, takes a boolean
		void action() override; //!< Action
	};

	/*! \class OpenGLSetBlendCommand
	\brief Render Command to enable/disable blending
	*/
	class OpenGLSetBlendCommand : public RenderCommand
	{
	private:
		bool m_enabled; //!< Enabled boolean
	public:
		OpenGLSetBlendCommand(bool enabled) : m_enabled(enabled) {}; //!< Constructor, takes a boolean
		void action() override; //!< Action
	};
}