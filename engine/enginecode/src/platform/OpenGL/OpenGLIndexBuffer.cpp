/*! \file OpenGLIndexBuffer.cpp */

#include "engine_pch.h"
#include <glad/glad.h>
#include "platform/OpenGL/OpenGLIndexBuffer.h"

namespace Engine
{
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t * indices, uint32_t count) : m_count(count)
	{
		glCreateBuffers(1, &m_OpenGL_ID); //!< Create an index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_OpenGL_ID); //!< Bind the index buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * count, indices, GL_DYNAMIC_DRAW); //!< Set the buffer's data size and data
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_OpenGL_ID); //!< Delete the buffer
	}
	void OpenGLIndexBuffer::edit(uint32_t * indices, uint32_t count, uint32_t offset)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_OpenGL_ID); //!< Rebind the buffer
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, sizeof(int32_t) * count, indices); //!< Update the buffer's datta and size
	}
}