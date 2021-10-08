/*! \file OpenGLRenderCommands.cpp */
#include "engine_pch.h"
#include <glad/glad.h>
#include "renderer/OpenGLRenderCommands.h"

namespace Engine
{
	void OpenGLClearDepthColourCommand::action()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //!< Clear the colour and depth buffers
	}

	void OpenGLClearDepthBufferCommand::action()
	{
		glClear(GL_DEPTH_BUFFER_BIT); //!< Clear the depth buffer
	}

	void OpenGLSetDepthTestCommand::action()
	{
		if (m_enabled)
		{
			glEnable(GL_DEPTH_TEST); //!< Enable the depth testing
		}
		else
		{
			glDisable(GL_DEPTH_TEST); //!< Or disable the depth testing
		}
	}

	void OpenGLSetClearColourCommand::action()
	{
		glClearColor(m_r, m_g, m_b, m_a); //!< Set the background colour
	}

	void OpenGLSetBackfaceCullingCommand::action()
	{
		if (m_enabled)
		{
			glEnable(GL_CULL_FACE); //!< Enable face culling
			glCullFace(GL_BACK); //!< Cull the back face
		}
		else
		{
			glDisable(GL_CULL_FACE); //!< Disable face culling
		}
	}

	void OpenGLSetBlendCommand::action()
	{
		if (m_enabled)
		{
			glEnable(GL_BLEND); //!< enable blending
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //!< Sets the blend method's sfactor and dfactor
		}
		else
		{
			glDisable(GL_BLEND); //!< Disables blending
		}
	}
}