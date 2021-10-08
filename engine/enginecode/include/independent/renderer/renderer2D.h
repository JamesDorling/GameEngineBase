/*! \file renderer2D */
#pragma once

#include "rendererCommon.h"

#include "ft2build.h"
#include "freetype/freetype.h"

namespace Engine
{
	/* \class Quad
	* \brief A class used by the 2d renderer as its version of 'material'
	*/
	class Quad
	{
	public:
		Quad() = default; //!< Default constructor
		static Quad createCentreHalfExtend(const glm::vec2& centre, const glm::vec2& halfExtents); //!< Create the quad from vec2 half extents
		static Quad createCentreHalfExtend(const glm::vec2& centre, float halfExtents); //!< Create the quad from float half extents
		static Quad createTopLeftSize(const glm::vec2& topLeft, const glm::vec2& size); //!< Create the quad from the top left coordinate and the size as a vec2
		static Quad createTopLeftSize(const glm::vec2& topLeft, float size); //!< Create the quad from the top left coordinate and the size as a float
		static Quad createTopLeftBottomRight(const glm::vec2& topLeft, const glm::vec2& bottomRight); //!< Create the quad from the top left coordinate and the bottom right coordinate
	private:
		glm::vec3 m_translate = glm::vec3(0.f); //!< Translate
		glm::vec3 m_scale = glm::vec3(1.f); //!< Scale
		friend class Renderer2D; //!< Friend class so that the renderer can change the translate and scale
	};

	/* \class Renderer2D
	* brief Class for rendering 2D primitives
	*/
	class Renderer2D
	{
	public:
		static void init(); //!< Initialise the internal data of the renderer
		static void begin(const SceneWideUniform& sceneWideUniform); //!< Begin a new 2D scene
		static void submit(const Quad& quad, const glm::vec4& tint); //!< Submit some primitives to be rendered
		static void submit(const Quad& quad, const std::shared_ptr<Texture>& texture); //!< Render a rextured quad
		static void submit(const Quad& quad, const glm::vec4& tint, const std::shared_ptr<Texture>& texture); //!< Textured quad wiht a tint
		static void submit(const Quad& quad, const glm::vec4& tint, const std::shared_ptr<Texture>& texture, float angle, bool degrees = false); //!< rotated quad
		static void submit(const Quad& quad, const std::shared_ptr<Texture>& texture, float angle, bool degrees = false); //!< rotated quad no tint
		static void submit(const Quad& quad, const glm::vec4& tint, float angle, bool degrees = false); //!< rotated quad no texture

		static void submit(char txt, const glm::vec2& position, float& advance, const glm::vec4& tint); //!< render a single char
		static void submit(const char * txt, const glm::vec2& position, const glm::vec4& tint); //!< render a single char

		static void end(); //!< End the current 2D scene
	private:
		struct InternalData
		{
			std::shared_ptr<Texture> defaultTexture; //!< Empty texture for default
			glm::vec4 defaultTint; //!< Plain white tint for default
			std::shared_ptr<Shader> shader; //!< Shader used
			std::shared_ptr<VertexArray> VAO; //!< Vertex array for a quad
			glm::mat4 model; //!< Model transform
			FT_Library ft; //!< Free type library
			FT_Face fontFace; //!< Font for the text
			std::shared_ptr<Texture> fontTexture; //!< Texture that is the glyph bitmap of the text
			glm::ivec2 glyphBufferDimensions; //!< Dimensions of the glyph buffer
			uint32_t glyphBufferSize; //!< Size of the glyph buffer
			std::shared_ptr<unsigned char> glyphBuffer; //!< glyphBuffer
		};

		static std::shared_ptr<InternalData> s_data; //!< pointer to the internal data

		static void RtoRGBA(unsigned char * Rbuffer, uint32_t width, uint32_t height); //!< Makes a bitmap of the text to render text
	};
}