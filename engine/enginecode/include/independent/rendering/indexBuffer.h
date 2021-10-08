/* \file indexBuffer.h */
#pragma once

#include <cstdint>

namespace Engine 
{
	/*! \class IndexBuffer
	* \brief API agnostic code for an index buffer
	*/
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default; //!< Destructor
		virtual inline uint32_t getRenderID() const = 0; //!< Getter for the rendering ID.
		virtual inline uint32_t getDrawCount() const = 0; //!< Getter for the draw count

		static IndexBuffer* create(uint32_t * indices, uint32_t count); //!< Creates the index buffer
	};
}