/* \file shader.h */
#pragma once

#include <cstdint>
#include <glm/glm.hpp>

namespace Engine
{
	/*! \class Shader
	* \brief API agnostic code for a shader
	*/
	class Shader
	{
	public:
		virtual ~Shader() = default; //!< Destructor
		virtual inline uint32_t getRenderID() const = 0; //!< Getter for the rendering ID.

		static Shader* create(const char* vertexFile, const char* fragmentFile); //!< Creates the shader using a vertex filepath and a fragment filepath
		static Shader* create(const char* filepath); //!< Creates the shader using a filepath

		virtual void uploadInt(const char* name, int value) = 0;					//!< Called to upload data to the shader in the form of an int 
		virtual void uploadFloat(const char* name, float value) = 0;				//!< Called to upload data to the shader in the form of a float
		virtual void uploadFloat2(const char* name, const glm::vec2& value) = 0;	//!< Called to upload data to the shader in the form of 2 floats (Vec2)
		virtual void uploadFloat3(const char* name, const glm::vec3& value) = 0;	//!< Called to upload data to the shader in the form of 3 floats (Vec3)
		virtual void uploadFloat4(const char* name, const glm::vec4& value) = 0;	//!< Called to upload data to the shader in the form of 4 floats (Vec4)
		virtual void uploadMat4(const char* name, const glm::mat4& value) = 0;		//!< Called to upload data to the shader in the form of a matrix (Mat4)
	};	
}