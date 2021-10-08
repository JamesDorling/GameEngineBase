/*! \file subTexture.cpp */

#include "engine_pch.h"
#include "rendering/subTexture.h"

namespace Engine
{
	SubTexture::SubTexture(const std::shared_ptr<Texture>& texture, const glm::vec2 & UVStart, const glm::vec2 & UVEnd) : m_texture(texture), m_UVStart(UVStart), m_UVEnd(UVEnd)
	{
		m_size.x = static_cast<int32_t>((UVEnd.x - UVStart.x) * m_texture->getWidthf()); //!< Get the width that should be used of the texture
		m_size.y = static_cast<int32_t>((UVEnd.y - UVStart.y) * m_texture->getHeightf());  //!< Get the height that should be used of the texture
	}
}