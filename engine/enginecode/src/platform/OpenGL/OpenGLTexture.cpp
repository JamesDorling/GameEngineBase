/* \file OpenGLTexture.cpp */

#include "engine_pch.h"
#include <glad/glad.h>

#include "platform/OpenGL/OpenGLTexture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Engine
{
	OpenGLTexture::OpenGLTexture(const char * filepath)
	{
		int32_t width, height, channels; //!< set the width, height and channels
		unsigned char *data = stbi_load(filepath, &width, &height, &channels, 0); //!< get the filepath

		if (data) { init(width, height, channels, data); } //!< If there is data, initialise it

		stbi_image_free(data); //!< Load the texture
	}

	OpenGLTexture::OpenGLTexture(uint32_t width, uint32_t height, uint32_t channels, unsigned char * data)
	{
		init(width, height, channels, data); //!< Initialise the data passed
	}

	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &m_OpenGL_ID); //!< Delete the texture
	}

	void OpenGLTexture::edit(uint32_t xOffset, uint32_t yOffset, uint32_t width, uint32_t height, unsigned char * data)
	{
		glBindTexture(GL_TEXTURE_2D, m_OpenGL_ID); //!< Bind the texture
		if (data)
		{
			if (m_channels == 3) glTextureSubImage2D(m_OpenGL_ID, 0, xOffset, yOffset, width, height, GL_RGB, GL_UNSIGNED_BYTE, data); //!< If there are 3 channels set the texture to just use RGB
			else if (m_channels == 4)  glTextureSubImage2D(m_OpenGL_ID, 0, xOffset, yOffset, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data); //!< If there are the 4 channels set the textuer to just use RGBA
			else return;
		}
	}

	void OpenGLTexture::init(uint32_t width, uint32_t height, uint32_t channels, unsigned char * data)
	{
		glGenTextures(1, &m_OpenGL_ID); //!< Generate the texture
		glBindTexture(GL_TEXTURE_2D, m_OpenGL_ID); //!< Bind the texture

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //!< Set the texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); //!< Set the texture parameters

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //!< Set the texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //!< Set the texture parameters

		if (channels == 3) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); //!< If there are 3 channels set the texture image to use RGB
		else if (channels == 4) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); //!< If there are 4 channels set the texture image to use RGBA
		else return;
		glGenerateMipmap(GL_TEXTURE_2D); //!< Generate the mipmap of the texture
		
		m_width = width; //!< Define the width
		m_height = height; //!< Define the height
		m_channels = channels; //!< Define the channels
	}
}