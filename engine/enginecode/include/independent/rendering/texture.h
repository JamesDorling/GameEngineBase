/* \file texture.h */
#pragma once

#include "rendering/bufferLayout.h"

namespace Engine
{
	/**
	* \class Texture
	* API Agnostic code for a texture
	*/
	class Texture
	{
	public:
		virtual ~Texture() = default; //!< Destructor

		virtual inline uint32_t getRenderID() const = 0; //!< Getter for the rendering ID.
		virtual inline uint32_t getWidth() = 0; //!< Getter for the width.
		virtual inline uint32_t getHeight() = 0;  //!< Getter for the width.
		virtual inline float getWidthf() = 0; //!< Getter for the width as a float
		virtual inline float getHeightf() = 0; //!< Getter for the height as a float
		virtual inline uint32_t getChannels() = 0;//!< Getter for the channels

		virtual void edit(uint32_t xOffset, uint32_t yOffset, uint32_t width, uint32_t height, unsigned char * data) = 0; //!< Edits the texture's attributes

		static Texture* create(const char* filepath); //!< Creates the texture
		static Texture* create(uint32_t width, uint32_t height, uint32_t channels, unsigned char * data); //!< Create texture from data
	};
}