/*! \file OpenGLShader.h */
#pragma once

#include <stdint.h>
#include "rendering/shader.h"

namespace Engine
{
	enum shaderType 
	{
		none = -1, 
		Vertex = 0, 
		Fragment, 
		Geometry, 
		TessellationControl, 
		TesselationEvaluation, 
		Compute 
	};

	/**
	* \class OpenGLShader
	* \brief This class is what handles the vertex and fragment shaders.
	*/
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const char* vertexFile, const char* fragmentFile); //!< Constructor, takes two filepaths to the vertex shader and fragment shader
		OpenGLShader(const char* filepath); //!< Constructor, takes a filepath
		virtual ~OpenGLShader(); //!< Deconstructor
		virtual inline uint32_t getRenderID() const override { return m_OpenGL_ID; } //!< Getter for the rendering ID.

		void uploadInt(const char* name, int value);				 //!< Called to upload data to the shader in the form of an int 
		void uploadFloat(const char* name, float value);			 //!< Called to upload data to the shader in the form of a float
		void uploadFloat2(const char* name, const glm::vec2& value); //!< Called to upload data to the shader in the form of 2 floats (Vec2)
		void uploadFloat3(const char* name, const glm::vec3& value); //!< Called to upload data to the shader in the form of 3 floats (Vec3)
		void uploadFloat4(const char* name, const glm::vec4& value); //!< Called to upload data to the shader in the form of 4 floats (Vec4)
		void uploadMat4(const char* name, const glm::mat4& value);	 //!< Called to upload data to the shader in the form of a matrix (Mat4)
	private:
		uint32_t m_OpenGL_ID;
		void compileAndLink(const char * vertexShaderSrc, const char * fragmentShaderSrc); //!< Compiles and links the fragment and vertex shaders together
	};
}