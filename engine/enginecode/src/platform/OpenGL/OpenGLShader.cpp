/*! \file OpenGLShader.cpp */

#include "engine_pch.h"
#include <glad/glad.h>
#include "platform/OpenGL/OpenGLShader.h"
#include <fstream>
#include "systems/log.h"
#include <string>
#include <array>
#include <glm/gtc/type_ptr.hpp>
namespace Engine 
{
	OpenGLShader::OpenGLShader(const char * vertexFile, const char * fragmentFile)
	{
		std::string  vertSrc, fragSrc, line; //!< pre-define the filepaths
		std::fstream handle(vertexFile, std::ios::in); //!< Use fStream to read from file
		if (handle.is_open())
		{
			while (getline(handle, line))
			{
				vertSrc += (line + "\n"); //!< Seperate the vertex block into lines
			}
		}
		else
		{
			Log::error("Could not load vertex shader file {0}", vertexFile); //!< If vertex shader didnt load, log it
			return;
		}
		handle.close(); //!< Close the file

		handle.open(fragmentFile, std::ios::in); //!< Open the fragment file
		if (handle.is_open())
		{

			while (getline(handle, line))
			{
				fragSrc += (line + "\n"); //!< Seperate the fragment file into lines
			}
		}
		else
		{
			Log::error("Could not load fragment shader file {0}", fragmentFile); //!< If fragment shader didnt load, log it
			return;
		}
		handle.close(); //!< Close the file

		compileAndLink(vertSrc.c_str(), fragSrc.c_str()); //!< Compile the shaders and link them
		//Converted to string here as compileAndLink needs a (const char *)
	}

	OpenGLShader::OpenGLShader(const char * filepath)
	{
		std::string line; //!< String line
		std::array<std::string, shaderType::Compute + 1> src; //!< Src array with a string and a data type
		uint32_t type = shaderType::none; //!< Empty shader data type

		std::fstream handle(filepath, std::ios::in); //!< Open the file

		if (handle.is_open())
		{
			while (getline(handle, line))  //!< Seperate the shader into regions based on the regions in the shader file
			{
			if (line.find("#region Vertex") != std::string::npos) { type = shaderType::Vertex; continue; }
			if (line.find("#region Fragment") != std::string::npos) { type = shaderType::Fragment; continue; }
			if (line.find("#region Geometry") != std::string::npos) { type = shaderType::Geometry; continue; }
			if (line.find("#region TessellationControl") != std::string::npos) { type = shaderType::TessellationControl; continue; }
			if (line.find("#region TessellationEvaluation") != std::string::npos) { type = shaderType::TesselationEvaluation; continue; }
			if (line.find("#region Compute") != std::string::npos) { type = shaderType::Compute; continue; }
			if (type != shaderType::none) src[type] += (line + "\n");
			}
		}
		else
		{
			Log::error("Could not load shader: Type: {0}, Path: {1}", type, filepath); //!< if file couldnt be opened, log it
		}
		handle.close(); //!< Close the file

		compileAndLink(src[shaderType::Vertex].c_str(), src[shaderType::Fragment].c_str()); //!< Compile and link the shader
		//Converted to string here as compileAndLink needs a (const char *)
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_OpenGL_ID); //!< Delete the shader
	}

	void OpenGLShader::uploadInt(const char * name, int value)
	{
		uint32_t uniformLocation = glGetUniformLocation(m_OpenGL_ID, name); //!< Get the uniform block's location
		glUniform1i(uniformLocation, value); //!< Upload the new data
	}

	void OpenGLShader::uploadFloat(const char * name, float value)
	{
		uint32_t uniformLocation = glGetUniformLocation(m_OpenGL_ID, name); //!< Get the uniform block's location
		glUniform1f(uniformLocation, value); //!< Upload the new data
	}

	void OpenGLShader::uploadFloat2(const char * name, const glm::vec2 & value)
	{
		uint32_t uniformLocation = glGetUniformLocation(m_OpenGL_ID, name); //!< Get the uniform block's location
		glUniform2f(uniformLocation, value.x, value.y); //!< Upload the new data
	}

	void OpenGLShader::uploadFloat3(const char * name, const glm::vec3 & value)
	{
		uint32_t uniformLocation = glGetUniformLocation(m_OpenGL_ID, name); //!< Get the uniform block's location
		glUniform3f(uniformLocation, value.x, value.y, value.z); //!< Upload the new data
	}

	void OpenGLShader::uploadFloat4(const char * name, const glm::vec4 & value)
	{
		uint32_t uniformLocation = glGetUniformLocation(m_OpenGL_ID, name); //!< Get the uniform block's location
		glUniform4f(uniformLocation, value.x, value.y, value.z, value.w); //!< Upload the new data
	}

	void OpenGLShader::uploadMat4(const char * name, const glm::mat4 & value)
	{
		uint32_t uniformLocation = glGetUniformLocation(m_OpenGL_ID, name); //!< Get the uniform block's location
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value)); //!< Upload the new data
	}

	void OpenGLShader::compileAndLink(const char * vertexShaderSrc, const char * fragmentShaderSrc)
	{
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); //!< Create the shader

		const GLchar* source = vertexShaderSrc; //!< Get the vertex shader source
		glShaderSource(vertexShader, 1, &source, 0); //!< Set the source
		glCompileShader(vertexShader); //!< Compile the shader

		GLint isCompiled = 0; //!< GLint for if shader compiled
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled); //!< Get the shader
		if (isCompiled == GL_FALSE) //!< If shader has not compiled
		{
			GLint maxLength = 0; //!< Max length for the info log and shader
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength); //!< Get the shader iv

			std::vector<GLchar> infoLog(maxLength); //!< Set the info log to a vector of chars
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]); //!< Get the shader info log
			Log::error("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end())); //!< Log the shader's compile errors

			glDeleteShader(vertexShader); //!< Delete the shader Gluint
			return;
		}

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //!< create the fragment shader

		source = fragmentShaderSrc;  //!< Get the fragment shader source
		glShaderSource(fragmentShader, 1, &source, 0); //!< set the source
		glCompileShader(fragmentShader); //!< Compile the fragment shader

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled); //!< get the shader
		if (isCompiled == GL_FALSE) //!< If the shader is not compiled
		{
			GLint maxLength = 0; //!< Get the info log max length
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength); //!< Get the shader iv

			std::vector<GLchar> infoLog(maxLength); //!< Create a vector of chars for the info log
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]); //!< Give the info log the shader's info log
			Log::error("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end())); //!< Log the info log

			glDeleteShader(fragmentShader); //!< Delete the frag shader
			glDeleteShader(vertexShader); //!< Delete the vert shader

			return;
		}

		m_OpenGL_ID = glCreateProgram(); //!< Create the program with the openglID
		glAttachShader(m_OpenGL_ID, vertexShader); //!< Attach the vertex shader
		glAttachShader(m_OpenGL_ID, fragmentShader); //!< Attach the fragment shader
		glLinkProgram(m_OpenGL_ID); //!< Link the program

		GLint isLinked = 0; //!< if the program is linked
		glGetProgramiv(m_OpenGL_ID, GL_LINK_STATUS, (int*)&isLinked); //!< Get the program iv
		if (isLinked == GL_FALSE) //!< if the program fails to link
		{
			GLint maxLength = 0; //!< Get the info log max length
			glGetProgramiv(m_OpenGL_ID, GL_INFO_LOG_LENGTH, &maxLength); //!< get the program IV

			std::vector<GLchar> infoLog(maxLength); //!< Set the info log max length as a vector of chars
			glGetProgramInfoLog(m_OpenGL_ID, maxLength, &maxLength, &infoLog[0]); //!< get the program info log
			Log::error("Shader linking error: {0}", std::string(infoLog.begin(), infoLog.end())); //!< Log the fragment error

			glDeleteProgram(m_OpenGL_ID); //!< Delete the program
			glDeleteShader(vertexShader); //!< Delete the vertex shader
			glDeleteShader(fragmentShader); //!< Delete the fragment shader

			return;
		}

		glDetachShader(m_OpenGL_ID, vertexShader); //!< Detach the vertex shader
		glDetachShader(m_OpenGL_ID, fragmentShader); //!< Detach the fragment shader
	}
}