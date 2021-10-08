/* \file vertexBuffer.h */
#pragma once

#include "rendering/bufferLayout.h"

namespace Engine
{
	/**
	* \class VertexBuffer
	* API Agnostic code for a vertex buffer
	*/
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default; //!< Destructor

		virtual inline uint32_t getRenderID() = 0; //!< Getter for the rendering ID.
		virtual inline const VertexBufferLayout& getLayout() const = 0; //!< Getter for the layout

		static VertexBuffer* create(void* vertices, uint32_t size, const VertexBufferLayout& layout); //!< Creates a pointer to a Vertex Buffer
	};
}