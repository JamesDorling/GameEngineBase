/*! \file OpenGLIndexBuffer.h */
#pragma once

#include "rendering/indexBuffer.h"

namespace Engine
{
	/**
	* \class OpenGLIndexBuffer
	* \brief This class creates the index buffer.
	*/
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t * indices, uint32_t count); //!< Constructor, takes the indices and a draw count as parameters.
		virtual ~OpenGLIndexBuffer(); //!< Destructor
		void edit(uint32_t * indices, uint32_t count, uint32_t offset); //!< Edit the index buffer 
		virtual inline uint32_t getRenderID() const override { return m_OpenGL_ID; } //!< Getter for the rendering ID.
		virtual inline uint32_t getDrawCount() const override { return m_count; } //!< Getter for the draw count
	private:
		uint32_t m_count; //!< Effective draw count
		uint32_t m_OpenGL_ID; //!< Render ID
	};
}