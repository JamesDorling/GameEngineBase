/*! \file GLFW_OpenGL_GC.cpp */
#include "engine_pch.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "platform/GLFW/GLFW_OpenGL_GC.h"
#include"systems/log.h"

namespace Engine 
{
	void errorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
	{
		Log::error("System fatal, graphics context error. Source: {0}, Type: {1}, ID: {2}, Severity: {3}, Length: {4}, Message: {5}, User Parameters: {6}", 
			source, 
			type, 
			id, 
			severity, 
			length, 
			message, 
			userParam); //!< Called on error, logs the error message
	}

	void GLFW_OpenGL_GC::init()
	{
		glfwMakeContextCurrent(m_window); //!< Makes the context apply to the current window
		auto result = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)); //!< Load the graphics context
		if (!result) 
		{
			Log::error("Failed to load OpenGL context for current GLFW window: {0}", result); //!< If graphics context fails to load, log it
		}

		//Enabling OpenGL debugging
		glEnable(GL_DEBUG_OUTPUT);//!< Enable the debugging output
		glDebugMessageCallback(
			[](GLenum source,
				GLenum type,
				GLuint id,
				GLenum severity,
				GLsizei length,
				const GLchar *message,
				const void *userParam
				) //!< Lambda function for the debug message callback
		{
			switch (severity) //!< Switch for severity on how the message should be logged
			{
			case GL_DEBUG_SEVERITY_HIGH:
				Log::error(message); //!< High severity is logged as an error
				break;
			case GL_DEBUG_SEVERITY_MEDIUM:
				Log::warn(message); //!< medium severity is logged as a warning
				break;

			case GL_DEBUG_SEVERITY_LOW:
				Log::info(message); //!< Low severity is logged as information
				break;

			case GL_DEBUG_SEVERITY_NOTIFICATION:
				Log::trace(message); //!< notification severity is logged with the lowest importance
				break;

			}
		}, 
			nullptr);
	}

	void GLFW_OpenGL_GC::swapBuffers()
	{
		glfwSwapBuffers(m_window); //!< swap the buffers
	}
}