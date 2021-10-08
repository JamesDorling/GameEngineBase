/*! \file OpenGLVertexArray */

#include "engine_pch.h"
#include <glad/glad.h>
#include "platform/OpenGL/OpenGLVertexArray.h"
#include "systems/log.h"

namespace Engine
{
	namespace SDT
	{
		static GLenum toGLType(ShaderDataType type)
		{
			switch (type) //!< Return the data types that the shader will be taking
			{
			case ShaderDataType::Short: return GL_SHORT;
			case ShaderDataType::Short2: return GL_SHORT;
			case ShaderDataType::Short3: return GL_SHORT;
			case ShaderDataType::Short4: return GL_SHORT;
			case ShaderDataType::Float: return GL_FLOAT;
			case ShaderDataType::Float2: return GL_FLOAT;
			case ShaderDataType::Float3: return GL_FLOAT;
			case ShaderDataType::Float4: return GL_FLOAT;
			case ShaderDataType::Byte4: return GL_UNSIGNED_BYTE;
			case ShaderDataType::Int: return GL_INT;
			//case ShaderDataType::Mat4: return GL_FLOAT_MAT4;
			//case ShaderDataType::Mat3: return GL_FLOAT_MAT3;
			default: return GL_INVALID_ENUM;
			}
		}
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_OpenGL_ID); //!< Create a vertex array
		glBindVertexArray(m_OpenGL_ID); //!< Bind the vertex array
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_OpenGL_ID); //!< Delete the vertex array
	}

	void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		m_vertexBuffer.push_back(vertexBuffer); //!< Push the vertex buffer

		glBindVertexArray(m_OpenGL_ID); //!< Bind the vertex array
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->getRenderID()); //!< Bind the buffer

		const auto& layout = vertexBuffer->getLayout(); //!< Get the layout of the vertex buffer
		for (const auto& element : layout)
		{
			uint32_t normalised = GL_FALSE; //!< is it normalised?
			if (element.m_normalised) { normalised = GL_TRUE; } //!< If it is normalised the set normalised to true
			glEnableVertexAttribArray(m_attributeIndex); //!< Enable the attrubute index
			glVertexAttribPointer(
				m_attributeIndex, 
				SDT::componentCount(element.m_dataType), 
				SDT::toGLType(element.m_dataType), 
				normalised, 
				layout.getStride(), 
				(void*)element.m_offset); //!< Set a pointer to the vertex attributes
			m_attributeIndex += 1; //!< Increment the attribute index
			//Log::info("Attribute Index = {0}", m_attributeIndex);
			//Log::info("Component Count = {0}", SDT::componentCount(element.m_dataType));
			//Log::info("GL Type = {0}", SDT::toGLType(element.m_dataType));
			//Log::info("Normalised = {0}", normalised);
			//Log::info("Stride = {0}", layout.getStride());
			//Log::info("Offset = {0}", (void*)element.m_offset);
		}
	}

	void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		m_indexBuffer = indexBuffer; //!< assign the index buffer
	}
}