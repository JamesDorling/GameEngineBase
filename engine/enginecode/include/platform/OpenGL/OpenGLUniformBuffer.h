/*! \file OpenGLUniformBuffer

*/
#pragma once

#include "rendering/uniformBuffer.h"

namespace Engine
{
	/*! \class OpenGLUniformBuffer
	* /brief Opengl specific uniform buffer layout
	*/
	class OpenGLUniformBuffer : public UniformBuffer
	{
	public:
		OpenGLUniformBuffer(const UniformBufferLayout& layout); //!< Constructor
		~OpenGLUniformBuffer(); //!< Destructor
		inline uint32_t getRenderID() override { return m_OpenGL_ID; } //!< Getter for the render ID
		inline UniformBufferLayout getLayout() { return m_layout; } //!< Getter for the layout
		void attachShaderBlock(const std::shared_ptr<Shader>& shader, const char * blockName) override; //!< Attach the shader block
		void uploadShaderData(const char * uniformName, void * data) override; //!< Upload data to the shader
	private:
		uint32_t m_OpenGL_ID; //!< OpenGL ID
		static uint32_t s_blockNo; //!< Global-ish block number that will increment with the constructor.
	};
}