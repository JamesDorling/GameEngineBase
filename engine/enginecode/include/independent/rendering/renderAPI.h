/* \file renderAPI.h */
#pragma once

namespace Engine
{
	class RenderAPI
	{
	public:
		/*! \enum API 
		\brief Enum that holds the APIs
		*/
		enum class API { None = 0, OpenGL = 1, Direct3D = 2, Vulkan = 3 };
		inline static API getAPI() { return s_API; } //!< Getter for the API
	private:
		static API s_API; //!< Current API
	};
}