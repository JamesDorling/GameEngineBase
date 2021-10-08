/*! \file OpenGLTexture.h */
#pragma once

#include <cstdint>
#include "rendering/texture.h"

namespace Engine 
{
	/*! \class OpenGLTexture
	* \brief Class for handling Open GL's textures
	*/
	class OpenGLTexture : public Texture
	{
	public:
		OpenGLTexture(const char * filepath); //!< Constructor that takes a file path
		OpenGLTexture(uint32_t width, uint32_t height, uint32_t channels, unsigned char * data); //!< Constructor, takes the width, height, channels and a filepath
		virtual ~OpenGLTexture(); //!< Destructor
		virtual void edit(uint32_t xOffset, uint32_t yOffset, uint32_t width, uint32_t height, unsigned char * data) override; //!< Edits the texture's data
		virtual inline uint32_t getRenderID() const override { return m_OpenGL_ID; } //!< Getter for the rendering ID.
		virtual inline uint32_t getWidth() override { return m_width; } //!< Getter for the width.
		virtual inline uint32_t getHeight() override { return m_height; } //!< Getter for the width.
		virtual inline float getWidthf() override { return { static_cast<float>(m_width) }; } //!< Getter for the width as a float
		virtual inline float getHeightf() override { return { static_cast<float>(m_height) }; } //!< Getter for the height as a float
		virtual inline uint32_t getChannels() override { return m_channels; } //!< Getter for the channels
	private:
		uint32_t m_OpenGL_ID; //!< Render ID
		uint32_t m_width, m_height, m_channels; //!< Width, height and channels
		void init(uint32_t width, uint32_t height, uint32_t channels, unsigned char * data); //!< Initialise the texture
	};
}