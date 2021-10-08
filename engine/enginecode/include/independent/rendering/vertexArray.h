/* \file vertexArray.h */
#pragma once

#include <cstdint>
#include <memory>

#include "rendering/vertexBuffer.h"
#include "rendering/indexBuffer.h"

namespace Engine
{
	/*! \class VertexArray
	* \brief API agnostic code for a vertex array
	*/
	class VertexArray
	{
	public:
		virtual ~VertexArray() = default; //!< Destructor
		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0; //!< Adds a vertex buffer to the array
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0; //!< Sets the index buffer
		virtual inline uint32_t getRenderID() const = 0; //!< Getter for the rendering ID.
		virtual inline uint32_t getDrawCount() const = 0; //!< Getter for the draw count
		virtual inline std::shared_ptr<IndexBuffer> getIndexBuffer() = 0; //!< Getter for the index buffer

		virtual inline std::shared_ptr<VertexBuffer> getVertexBuffer(uint32_t index) = 0; //!< Getter for the vertex buffer



		static VertexArray* create(); //!< Creates a pointer to a vertex array
	};
}