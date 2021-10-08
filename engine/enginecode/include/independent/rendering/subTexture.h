/*! \file subTexture.h*/
#pragma once

#include "rendering/texture.h"
#include <memory>
#include <glm/glm.hpp>

namespace Engine
{
	/*! \class SubTexture
	* \brief class for cutting texture maps into smaller textures
	*/
	class SubTexture
	{
	public:
		SubTexture() {} //!< Default constructor
		SubTexture(const std::shared_ptr<Texture>& texture, const glm::vec2& UVStart, const glm::vec2& UVEnd);

		inline glm::vec2 getUVStart() { return m_UVStart; } //!< Getter for the UV starting coordinate
		inline glm::vec2 getUVEnd() { return m_UVEnd; } //!< Getter for the UV end coordinate
		inline glm::ivec2 getSize() { return m_size; }  //!< Getter for the size in pixels
		inline glm::vec2 getSizef() { return { static_cast<float>(m_size.x), static_cast<float>(m_size.y) }; } //!< Returns the size in float values
		inline uint32_t getWidth() { return m_size.x; } //!< Getter for the width of the texture atlus
		inline uint32_t getHeight() { return m_size.y; } //!< Getter for the width of the texture atlus
		inline float getWidthf() { return static_cast<float>(m_size.x); } //!< Getter for the width of the texture atlus in float form
		inline float getHeightf() { return static_cast<float>(m_size.y); } //!< Getter for the height of the texture atlus in float form
		inline uint32_t getUVWidth() { return static_cast<int32_t>(m_UVEnd.x - m_UVStart.x); } //!< Getter for the width of the UV
		inline uint32_t getUVHeight() { return static_cast<int32_t>(m_UVEnd.y - m_UVStart.y); } //!< Getter for the height of the UV
		inline float getUVWidthf() { return m_UVEnd.x - m_UVStart.x; } //!< Getter for the width of the UV as a float
		inline float getUVHeightf() { return m_UVEnd.y - m_UVStart.y; } //!< Getter for the height of the UV as a float

		inline float transformU(float U) { return m_UVStart.x + (getUVWidthf() * U); } //!< Transform original to atlased coordinates (takes x)
		inline float transformV(float V) { return m_UVStart.y + (getUVHeightf() * V); } //!< Transform original to atlased coordinates (takes y)
		inline glm::vec2 transformUV(glm::vec2 UV) { return m_UVStart + ((m_UVEnd - m_UVStart) * UV); } //!< Transform original to atlased coordinates (takes both x and y)
	private:
		std::shared_ptr<Texture> m_texture; //!< Texture (UV atlas)
		glm::vec2 m_UVStart, m_UVEnd; //!< UV start and end points
		glm::ivec2 m_size; //!< Size in pixels
	};
}