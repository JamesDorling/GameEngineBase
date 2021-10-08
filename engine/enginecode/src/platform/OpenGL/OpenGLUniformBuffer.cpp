/*! \file OpenGLUniformBuffer.cpp  */
#include "engine_pch.h"
#include <glad/glad.h>

#include "platform/OpenGL/OpenGLUniformBuffer.h"

namespace Engine
{
	uint32_t OpenGLUniformBuffer::s_blockNo = 0; //!< Initialise the static member block number
	OpenGLUniformBuffer::OpenGLUniformBuffer(const UniformBufferLayout & layout)
	{
		m_blockNo = s_blockNo; //!< Initialise the block number
		s_blockNo++; //!< Increment the block number

		m_layout = layout; //!< Define the layout
		glGenBuffers(1, &m_OpenGL_ID); //!< Generate a buffer
		glBindBuffer(GL_UNIFORM_BUFFER, m_OpenGL_ID); //!< Bind the buffer
		glBufferData(GL_UNIFORM_BUFFER, m_layout.getStride(), nullptr, GL_DYNAMIC_DRAW); //!< Set the buffer data
		glBindBufferRange(GL_UNIFORM_BUFFER, m_blockNo, m_OpenGL_ID, 0, m_layout.getStride()); //!< Bind the buffer range (max and min buffer range)

		for (auto& element : m_layout)
		{
			m_uniformCache[element.m_name] = std::pair<uint32_t, uint32_t>(element.m_offset, element.m_size); //!< For every element in the layout add it's offset and size to the uniformCache as a pair
		}
	}

	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		glDeleteBuffers(1, &m_OpenGL_ID); //!< Delete the uniform buffer
	}

	void OpenGLUniformBuffer::attachShaderBlock(const std::shared_ptr<Shader>& shader, const char * blockName)
	{
		uint32_t blockIndex = glGetUniformBlockIndex(shader->getRenderID(), blockName); //!< Get the block index
		glUniformBlockBinding(shader->getRenderID(), blockIndex, m_blockNo); //!< Bind the block
	}

	void OpenGLUniformBuffer::uploadShaderData(const char * uniformName, void * data)
	{
		auto& pair = m_uniformCache[uniformName]; //!< Take the uniform cache member
		glBindBuffer(GL_UNIFORM_BUFFER, m_OpenGL_ID); //!< Bind the buffer
		glBufferSubData(GL_UNIFORM_BUFFER, pair.first, pair.second, data); //!< update the buffer with the data fiven and the uniform cache data
	}
	
}