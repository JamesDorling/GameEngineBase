/*! \file OpenGLVertexBuffer */
#pragma once

#include "rendering/bufferLayout.h"
#include "rendering/vertexBuffer.h"
namespace Engine 
{
	/*!
	* \class OpenGLVertexBuffer
	* \brief This class creates the vertex buffer.
	*/
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(void* vertices, uint32_t size, VertexBufferLayout layout);//!< Constructor. Takes a pointer to the vertices, the size and a buffer layout.
		virtual ~OpenGLVertexBuffer(); //!< Deconstructor
		void edit(void* vertices, uint32_t size, uint32_t offset); //!< Edit is used for editing the vertex buffer at a later time. Does not require a layout as that is set in the constructor.
		virtual inline uint32_t getRenderID() override { return m_OpenGL_ID; } //!< Getter for the rendering ID.
		virtual inline const VertexBufferLayout& getLayout() const override { return m_layout; } //!< Getter for the layout
	private:
		uint32_t m_OpenGL_ID; //!< Vertex buffer rendering ID
		VertexBufferLayout m_layout; //!< Buffer layout
	};
}