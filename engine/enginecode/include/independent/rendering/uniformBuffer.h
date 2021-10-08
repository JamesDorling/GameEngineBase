/*! \file uniformBuffer.h 
\ \brief API agnostic code for the uniform buffer 
*/
#pragma once
#include "rendering/bufferLayout.h"
#include "rendering/shader.h"
#include <unordered_map>
#include <memory>
#include <glm/glm.hpp>

namespace Engine
{
	/*! \class UniformBuffer
	* \brief Base class for uniform buffers
	*/
	class UniformBuffer
	{
	public:
		virtual ~UniformBuffer() = default; //!< Destructor
		virtual inline uint32_t getRenderID() = 0; //!< Getter for the render ID
		virtual inline UniformBufferLayout getLayout() = 0; //!< Getter for the layout
		virtual void attachShaderBlock(const std::shared_ptr<Shader>& shader, const char * blockName) = 0; //!< Attaches the shader block
		virtual void uploadShaderData(const char * uniformName, void * data) = 0; //!< Uploades shader data
		static UniformBuffer* create(const UniformBufferLayout& layout); //!< Creates the Uniform Buffer
	protected:
		UniformBufferLayout m_layout; //!< Layout
		std::unordered_map<const char *, std::pair<uint32_t, uint32_t>> m_uniformCache; //!< Stores the uniform names, offsets and sizes in an unordered map so that it can be iterated later.
		uint32_t m_blockNo; //!< Block number for this UBO
		//glm::mat4 m_data[]; //for my attempt at making it upload once
	};
}