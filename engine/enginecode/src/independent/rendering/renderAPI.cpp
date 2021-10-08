/*! \file renderAPI.cpp */
#include "engine_pch.h"
#include "rendering/renderAPI.h"
#include "rendering/indexBuffer.h"
#include "platform/OpenGL/OpenGLIndexBuffer.h"
#include "systems/log.h"
#include "rendering/vertexArray.h"
#include "platform/OpenGL/OpenGLVertexArray.h"
#include "rendering/vertexBuffer.h"
#include "platform/OpenGL/OpenGLVertexBuffer.h"
#include "rendering/shader.h"
#include "platform/OpenGL/OpenGLShader.h"
#include "rendering/texture.h"
#include "platform/OpenGL/OpenGLTexture.h"
#include "rendering/uniformBuffer.h"
#include "platform/OpenGL/OpenGLUniformBuffer.h"

namespace Engine 
{ 
	RenderAPI::API RenderAPI::s_API = RenderAPI::API::OpenGL; 

	IndexBuffer* IndexBuffer::create(uint32_t * indices, uint32_t count)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Log::error("No render API chosen"); //!< This RenderAPI is not implemented
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, count); //!< Create a new index buffer
		case RenderAPI::API::Direct3D:
			Log::error("Direct3D not currently supported"); //!< This RenderAPI is not implemented
			break;
		case RenderAPI::API::Vulkan:
			Log::error("Vulkan not currently supported"); //!< This RenderAPI is not implemented
			break;
		}
		return nullptr;
	}

	VertexArray* VertexArray::create()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Log::error("No render API chosen"); //!< This RenderAPI is not implemented
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLVertexArray; //!< Return a new vertex array
		case RenderAPI::API::Direct3D:
			Log::error("Direct3D not currently supported"); //!< This RenderAPI is not implemented
			break;
		case RenderAPI::API::Vulkan:
			Log::error("Vulkan not currently supported"); //!< This RenderAPI is not implemented
			break;
		}
		return nullptr;
	}

	VertexBuffer* VertexBuffer::create(void* vertices, uint32_t size, const VertexBufferLayout& layout)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Log::error("No render API chosen"); //!< This RenderAPI is not implemented
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLVertexBuffer(vertices, size, layout); //!< Return a new vertex buffer
		case RenderAPI::API::Direct3D:
			Log::error("Direct3D not currently supported"); //!< This RenderAPI is not implemented
			break;
		case RenderAPI::API::Vulkan:
			Log::error("Vulkan not currently supported"); //!< This RenderAPI is not implemented
			break;
		}
		return nullptr;
	}

	Shader* Shader::create(const char* vertexFile, const char* fragmentFile)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Log::error("No render API chosen"); //!< This RenderAPI is not implemented
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLShader(vertexFile, fragmentFile); //!< Return a new shader
		case RenderAPI::API::Direct3D:
			Log::error("Direct3D not currently supported"); //!< This RenderAPI is not implemented
			break;
		case RenderAPI::API::Vulkan:
			Log::error("Vulkan not currently supported"); //!< This RenderAPI is not implemented
			break; 
		}
		return nullptr;
	}

	Shader* Shader::create(const char* filepath)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Log::error("No render API chosen"); //!< This RenderAPI is not implemented
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLShader(filepath); //!, Return a new shader
		case RenderAPI::API::Direct3D:
			Log::error("Direct3D not currently supported"); //!< This RenderAPI is not implemented
			break;
		case RenderAPI::API::Vulkan:
			Log::error("Vulkan not currently supported"); //!< This RenderAPI is not implemented
			break;
		}
		return nullptr;
	}

	Texture* Texture::create(const char* filepath)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Log::error("No render API chosen"); //!< This RenderAPI is not implemented
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLTexture(filepath); //!, Return a new texture
		case RenderAPI::API::Direct3D:
			Log::error("Direct3D not currently supported"); //!< This RenderAPI is not implemented
			break;
		case RenderAPI::API::Vulkan:
			Log::error("Vulkan not currently supported"); //!< This RenderAPI is not implemented
			break;
		}
		return nullptr;
	}

	Texture* Texture::create(uint32_t width, uint32_t height, uint32_t channels, unsigned char * data)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Log::error("No render API chosen"); //!< This RenderAPI is not implemented
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLTexture(width, height, channels, data); //!< Return a new texture
		case RenderAPI::API::Direct3D:
			Log::error("Direct3D not currently supported"); //!< This RenderAPI is not implemented
			break;
		case RenderAPI::API::Vulkan:
			Log::error("Vulkan not currently supported"); //!< This RenderAPI is not implemented
			break;
		}
		return nullptr;
	}

	UniformBuffer* UniformBuffer::create(const UniformBufferLayout& layout)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Log::error("No render API chosen"); //!< This RenderAPI is not implemented
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLUniformBuffer(layout); //!< Return a new uniform buffer
		case RenderAPI::API::Direct3D:
			Log::error("Direct3D not currently supported"); //!< This RenderAPI is not implemented
			break;
		case RenderAPI::API::Vulkan:
			Log::error("Vulkan not currently supported"); //!< This RenderAPI is not implemented
			break;
		}
		return nullptr;
	}

}