/*! \file rendererCommon 
* \brief A file that contains common includes for the renderers
*/
#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include <memory>
#include "rendering/shaderDataType.h"
#include "rendering/vertexArray.h"
#include "rendering/texture.h"
#include "rendering/shader.h"
#include "renderCommands.h"
#include "rendering/uniformBuffer.h"

namespace Engine 
{
	using SceneWideUniform = std::unordered_map<const char *, std::shared_ptr<UniformBuffer>>;

	/*! \class RendererCommon
	*/
	class RendererCommon
	{
	public:
		static void actionCommand(RenderCommand * command)
		{
			command->action(); //!< Do the command's action
			delete command; //!< Delete the pointer
		}
	};
}
