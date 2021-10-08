/*! \file OpenGLVertexArray.h */
#pragma once

#include <vector>
#include <memory>
#include "OpenGLVertexBuffer.h"
#include "OpenGLIndexBuffer.h"
#include "rendering/vertexArray.h"

namespace Engine
{
	/**
	* \class OpenGLVertexArray
	* \brief This class creates a vertex array. It utilises VertexBuffer.h.
	*/
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray(); //!< Constructor
		virtual ~OpenGLVertexArray(); //!< Destructor
		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override; //!< Adds a vertex buffer to the array
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override; //!< Sets the index buffer
		virtual inline std::shared_ptr<IndexBuffer> getIndexBuffer() override { return m_indexBuffer; } //!< Getter for the index buffer
		virtual inline uint32_t getDrawCount() const override { if (m_indexBuffer) { return m_indexBuffer->getDrawCount(); } else { return 0; }} //!< Getter for the index buffer draw count
		virtual inline uint32_t getRenderID() const override { return m_OpenGL_ID; } //!< Getter for the rendering ID.

		inline std::shared_ptr<VertexBuffer> getVertexBuffer(uint32_t index) { return m_vertexBuffer.at(index); } //!< Getter for the vertex buffer

	private:
		uint32_t m_OpenGL_ID; //!< Render ID
		uint32_t m_attributeIndex = 0; //!< Vertex Array Attribute Index number
		std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffer; //!< A vector that contains a pointer to a vertex buffer
		std::shared_ptr<IndexBuffer> m_indexBuffer; //!< Pointer to an index buffer
	};
}