/*! \file renderCommands.cpp */
#include "engine_pch.h"
#include <glad/glad.h>
#include "renderer/renderCommands.h"
#include "rendering/renderAPI.h"
#include "systems/log.h"
#include "renderer/OpenGLRenderCommands.h"

namespace Engine
{
	RenderCommand * RenderCommand::clearDepthColourCommand()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::Direct3D:
			Log::error("Renderer API not supported."); //!< This RenderAPI is not implemented
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLClearDepthColourCommand(); //!< Pass the command to openGL render commands
			break;
		case RenderAPI::API::Vulkan:
			Log::error("Renderer API not supported."); //!< This RenderAPI is not implemented
			break;
		case RenderAPI::API::None:
			Log::error("Renderer API not supported."); //!< This RenderAPI is not implemented
			break;
		default:
			Log::error("Renderer API not supported."); //!< This RenderAPI is not implemented
			break;
		}
	}

	RenderCommand * RenderCommand::setClearColourCommand(float r, float g, float b, float a)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::Direct3D:
			Log::error("Renderer API not supported."); //!< This RenderAPI is not implemented
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLSetClearColourCommand(r,g,b,a); //!< Pass the command to openGL render commands
			break;
		case RenderAPI::API::Vulkan:
			Log::error("Renderer API not supported."); //!< This RenderAPI is not implemented
			break;
		case RenderAPI::API::None:
			Log::error("Renderer API not supported."); //!< This RenderAPI is not implemented
			break;
		default:
			Log::error("Renderer API not supported."); //!< This RenderAPI is not implemented
			break;
		}
	}

	RenderCommand * RenderCommand::setDepthTestCommand(bool enabled)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::Direct3D:
			Log::error("Renderer API not supported."); //!< This RenderAPI is not implemented
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLSetDepthTestCommand(enabled); //!< Pass the command to openGL render commands
			break;
		case RenderAPI::API::Vulkan:
			Log::error("Renderer API not supported."); //!< This RenderAPI is not implemented
			break;
		case RenderAPI::API::None:
			Log::error("Renderer API not supported."); //!< This RenderAPI is not implemented
			break;
		default:
			Log::error("Renderer API not supported."); //!< This RenderAPI is not implemented
			break;
		}
	}

	RenderCommand * RenderCommand::setBackfaceCullingCommand(bool enabled)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::Direct3D:
			Log::error("Renderer API not supported."); //!< This RenderAPI is not implemented
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLSetBackfaceCullingCommand(enabled); //!< Pass the command to openGL render commands
			break;
		case RenderAPI::API::Vulkan:
			Log::error("Renderer API not supported."); //!< This RenderAPI is not implemented
			break;
		case RenderAPI::API::None:
			Log::error("Renderer API not supported."); //!< This RenderAPI is not implemented
			break;
		default:
			Log::error("Renderer API not supported."); //!< This RenderAPI is not implemented
			break;
		}
	}

	RenderCommand * RenderCommand::setBlendCommand(bool enabled)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::Direct3D:
			Log::error("Renderer API not supported."); //!< This RenderAPI is not implemented
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLSetBlendCommand(enabled); //!< Pass the command to openGL render commands
			break;
		case RenderAPI::API::Vulkan:
			Log::error("Renderer API not supported."); //!< This RenderAPI is not implemented
			break;
		case RenderAPI::API::None:
			Log::error("Renderer API not supported."); //!< This RenderAPI is not implemented
			break;
		default:
			Log::error("Renderer API not supported."); //!< This RenderAPI is not implemented
			break;
		}
	}

}