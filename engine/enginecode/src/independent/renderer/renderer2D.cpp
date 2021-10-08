/*! \file renderer2D */

#include "engine_pch.h"
#include "systems/log.h"
#include <glad/glad.h>
#include "renderer/renderer2D.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{
	std::shared_ptr<Renderer2D::InternalData> Renderer2D::s_data = nullptr;

	void Renderer2D::init()
	{
		s_data.reset(new InternalData); //!< Resets the s_data pointer to have a new internaldata
		unsigned char whitePix[4] = { 255, 255, 255, 255 }; //!< Creates a pure white pixel
		s_data->defaultTexture.reset(Texture::create(1, 1, 4, whitePix)); //!< Makes the default texture to be pure white

		s_data->defaultTint = { 1.f, 1.f, 1.f, 1.f }; //!< Default tint is white

		s_data->model = glm::mat4(1.0f); //!< Assigns the translate to be a matrix of 1s

		s_data->shader.reset(Shader::create("./assets/shaders/quad1.glsl"));//!< Sets the shader to be the quad1.glsl shader

		float vertices[4 * 4] = //!< Default square vertices
		{
			-0.5f, -0.5f, 0.f, 0.f,
			-0.5f,  0.5f, 0.f, 1.f,
			 0.5f,  0.5f, 1.f, 1.f,
			 0.5f, -0.5f, 1.f, 0.f
		};

		uint32_t indices[4] = { 0,1,2,3 }; //!< Indices of a square

		std::shared_ptr<VertexBuffer> VBO; //!< Pointer to a vertex buffer
		std::shared_ptr<IndexBuffer> IBO; //!< Pointer to an index buffer

		s_data->VAO.reset(VertexArray::create()); //!< creates the internal data's vertex array
		VBO.reset(VertexBuffer::create(vertices, sizeof(vertices), VertexBufferLayout({ ShaderDataType::Float2, ShaderDataType::Float2 }))); //!< Resets the vertexBuffer with a layout of two vec2s
		IBO.reset(IndexBuffer::create(indices, 4)); //!< Creates the indexbuffer on the pointer with the indices previously defined
		s_data->VAO->addVertexBuffer(VBO); //!< adds the vertex buffer to the vertex array
		s_data->VAO->setIndexBuffer(IBO); //!< Adds the index buffer to the vertex array


		//Font Filepath
		const char * fontFilePath = "./assets/fonts/cour.ttf"; //!< Defines the font's filepath

		//Glyph Buffer data
		s_data->glyphBufferDimensions = { 256, 256 }; //!< Sets the glyph's dimensions
		s_data->glyphBufferSize = s_data->glyphBufferDimensions.x * s_data->glyphBufferDimensions.y * 4 * sizeof(unsigned char); //!< Sets the glyph's size
		s_data->glyphBuffer.reset(static_cast<unsigned char *>(malloc(s_data->glyphBufferSize))); //!< creates the glyphbuffer

		//Init freetype
		if(FT_Init_FreeType(&s_data->ft)) Log::error("Error: Freetype could not be initialised"); //!< Initialises freetype

		//Load font
		if (FT_New_Face(s_data->ft, fontFilePath, 0, &s_data->fontFace)) Log::error("Could not load font face: {0}", fontFilePath); //!< Loads the font

		//set char size
		int32_t charSize = 100;
		if (FT_Set_Pixel_Sizes(s_data->fontFace, 0, charSize)) Log::error("Freetype failed to set font size of: {0}", charSize); //!< Sets the character size

		//Init font text
		s_data->fontTexture.reset(Texture::create(s_data->glyphBufferDimensions.x, s_data->glyphBufferDimensions.y, 4, nullptr)); //!< Sets the font texture via pointer reset

		//Fill glyph buffer
		memset(s_data->glyphBuffer.get(), 60, s_data->glyphBufferSize); //!< Fills the glyph buffer

		//send glyphBuffer to the texture on the gpu
		s_data->fontTexture->edit(0, 0, s_data->glyphBufferDimensions.x, s_data->glyphBufferDimensions.y, s_data->glyphBuffer.get()); //!< gives the GPU the glyph buffer

	}

	void Renderer2D::begin(const SceneWideUniform & sceneWideUniform)
	{
		//Bind shader
		glUseProgram(s_data->shader->getRenderID()); //!< Binds the shader

		//Apply scenewideuniform
		for (auto& dataPair : sceneWideUniform) //!< Goes through the scenewide uniforms and attaches them to the shader
		{
			const char* nameOfUniformBlock = dataPair.first;
			dataPair.second->attachShaderBlock(s_data->shader, nameOfUniformBlock);
		}

		//bind the geometry
		glBindVertexArray(s_data->VAO->getRenderID()); //!< binds the vertex array to the s_data vertex array
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_data->VAO->getIndexBuffer()->getRenderID()); //!< binds the index buffer to the GL element array buffer
	}

	void Renderer2D::submit(const Quad & quad, const glm::vec4 & tint)
	{
		Renderer2D::submit(quad, tint, s_data->defaultTexture); //!< Pass the parameters to a different submit, with the default texture
	}

	void Renderer2D::submit(const Quad & quad, const std::shared_ptr<Texture>& texture)
	{
		Renderer2D::submit(quad, s_data->defaultTint, texture); //!< Pass the parameters to a different submit, with the default tint
	}

	void Renderer2D::submit(const Quad & quad, const glm::vec4 & tint, const std::shared_ptr<Texture>& texture) //!< Sort of like a "Master Submit"
	{
		glBindTexture(GL_TEXTURE_2D, texture->getRenderID()); //!< Bind the 2D texture
		s_data->model = glm::scale(glm::translate(glm::mat4(1.f), quad.m_translate), quad.m_scale); //!< Translate and scale the model

		s_data->shader->uploadInt("u_texData", 0);			  //!< Upload the texData to the shader
		s_data->shader->uploadFloat4("u_tint", tint);		  //!< Upload tint to the shader
		s_data->shader->uploadMat4("u_model", s_data->model); //!< Upload model to the shader

		glDrawElements(GL_QUADS, s_data->VAO->getDrawCount(), GL_UNSIGNED_INT, nullptr); //!< Draw the quad
	}

	void Renderer2D::submit(const Quad & quad, const glm::vec4 & tint, const std::shared_ptr<Texture>& texture, float angle, bool degrees)
	{
		if (degrees) angle = glm::radians(angle); //!< Turn the degrees to radians if necessary

		glBindTexture(GL_TEXTURE_2D, texture->getRenderID()); //!< Bind the 2D texture
		s_data->model = glm::scale(glm::rotate(glm::translate(glm::mat4(1.f), quad.m_translate), angle, { 0.f, 0.f, 1.f }), quad.m_scale);  //!< Translate, scale and rotate the model

		s_data->shader->uploadInt("u_texData", 0);				//!< Upload the texData to the shader
		s_data->shader->uploadFloat4("u_tint", tint);			//!< Upload tint to the shader
		s_data->shader->uploadMat4("u_model", s_data->model);	//!< Upload model to the shader

		glDrawElements(GL_QUADS, s_data->VAO->getDrawCount(), GL_UNSIGNED_INT, nullptr); //!< draw the model
	}

	void Renderer2D::submit(const Quad & quad, const std::shared_ptr<Texture>& texture, float angle, bool degrees)
	{
		submit(quad, s_data->defaultTint, texture, angle, degrees); //!< Pass the parameters to a different submit with a default tint
	}

	void Renderer2D::submit(const Quad & quad, const glm::vec4 & tint, float angle, bool degrees)
	{
		submit(quad, tint, s_data->defaultTexture, angle, degrees); //!< Pass the parameters to a different submit with a default texture
	}

	void Renderer2D::submit(char txt, const glm::vec2 & position, float & advance, const glm::vec4& tint)
	{
		//Get glyph
		if (FT_Load_Char(s_data->fontFace, txt, FT_LOAD_RENDER)) Log::error("Could not load glyph for char: {0}", txt); //!< If the glyph char load fails then log it, else:
		else
		{
			//Glyph data
			uint32_t glyphWidth = s_data->fontFace->glyph->bitmap.width; //!< Defines the glyph's width
			uint32_t glyphHeight = s_data->fontFace->glyph->bitmap.rows; //!< Defines the glyph's height
			glm::vec2 glyphSize(glyphWidth, glyphHeight); //!< Sets the glyph's size to a vec2
			glm::vec2 glyphBearing(s_data->fontFace->glyph->bitmap_left, -s_data->fontFace->glyph->bitmap_top); //!< Set the glyph's bearing to a vec2 to get the glyph's position
			
			//Advance
			advance = static_cast<float>(s_data->fontFace->glyph->advance.x >> 6); //!< assigns the advance

			//Calc quad for the glyph
			glm::vec2 glyphPos = position + glyphBearing; //!< Defines the glyph position
			Quad quad = Quad::createTopLeftSize(glyphPos, glm::vec2(s_data->fontTexture->getWidthf(), s_data->fontTexture->getHeightf())); //!< creates a quad using the top left and the size 

			RtoRGBA(s_data->fontFace->glyph->bitmap.buffer, glyphWidth, glyphHeight); //!< Makes the text bitmap
			s_data->fontTexture->edit(0, 0, s_data->glyphBufferDimensions.x, s_data->glyphBufferDimensions.y, s_data->glyphBuffer.get()); //!< Passes the font 

			//Submit quad
			Renderer2D::submit(quad, tint, s_data->fontTexture); //!< Submits the quad through the "Master Submit"
		}
	}

	void Renderer2D::submit(const char * txt, const glm::vec2 & position, const glm::vec4& tint)
	{
		uint32_t length = strlen(txt); //!< Gets the length of the string
		float advance = 0.f, pos = position.x; //!< Gets the advance and current position
		for (int32_t i = 0; i < length; i++) //!< Seperates the string into individual chars and submits them
		{
			submit(txt[i], { pos, position.y }, advance, tint); //!< Submit the individual character
			pos += advance; //!< Move the position of the next character, so the characters dont stack
		}
	}

	void Renderer2D::end()
	{

	}

	void Renderer2D::RtoRGBA(unsigned char * Rbuffer, uint32_t width, uint32_t height)
	{
		memset(s_data->glyphBuffer.get(), 0, s_data->glyphBufferSize); //!< Set the memory of the glyphbuffer

		unsigned char * pWalker = s_data->glyphBuffer.get(); //!< Get the glyphBuffer
		for (int32_t i = 0; i < height; i++)//!< Goes along the height of the bitmap colouring pixels
		{
			for (int32_t j = 0; j < width; j++) //!< Goes along the width of the bitmap colouring pixels
			{
				//pWalker += 3;
				*pWalker = 255; pWalker++; //!< Sets the data  at pWalker to be 255, making it full. Then moves to the next address
				*pWalker = 255; pWalker++; //!< Sets the data  at pWalker to be 255, making it full. Then moves to the next address
				*pWalker = 255; pWalker++; //!< Sets the data  at pWalker to be 255, making it full. Then moves to the next address
				*pWalker = *Rbuffer; //!< Set the alpha channel
				pWalker++; //!< Goes to R of next pixel
				Rbuffer++; //!< Goes to next monochrome pixel
			}
			pWalker += (s_data->glyphBufferDimensions.x - width)  * 4; //!< adds the glyphbuffer's X axis dimensions minus the width to pWalker, multiplied by the number of channels (4)
		}

	}

	Quad Quad::createCentreHalfExtend(const glm::vec2& centre, const glm::vec2& halfExtents)
	{
		Quad result; //!< Pre-define result
		result.m_translate = glm::vec3(centre, 0.f); //!< Get the centre as a vec3
		result.m_scale = glm::vec3(halfExtents * 2.f, 1.f); //!< uses the half extents to get the scale, via doubling them to get the size
		return result; //!< Return the resulting quad
	}

	Quad Quad::createCentreHalfExtend(const glm::vec2& centre, float halfExtents)
	{
		Quad result; //!< Pre-define result
		result.m_translate = glm::vec3(centre, 0.f); //!< Get the centre as a vec3
		result.m_scale = glm::vec3(halfExtents * 2.f, halfExtents * 2.f, 1.f); //!< uses the half extent to get the scale, via doubling it to get the size
		return result; //!< Return the resulting quad
	}

	Quad Quad::createTopLeftSize(const glm::vec2& topLeft, const glm::vec2& size)
	{
		Quad result; //!< Pre-define result
		result.m_translate = glm::vec3(topLeft.x + (size.x / 2), topLeft.y + (size.y / 2), 0.f); //Plus on Y because higher numbers lower the block, Y axis is inverted
		result.m_scale = glm::vec3(size, 1.f); //!< turn size into a vec3
		return result; //!< Return the resulting quad
	}

	Quad Quad::createTopLeftSize(const glm::vec2& topLeft, float size)
	{
		Quad result; //!< Pre-define result
		result.m_translate = glm::vec3(topLeft.x + (size / 2), topLeft.y + (size / 2), 0.f); //Plus on Y because higher numbers lower the block, Y axis is inverted
		result.m_scale = glm::vec3(size, size, 1.f); //!< Turn size into a vec3
		return result; //!< Return the resulting quad
	}

	Quad Quad::createTopLeftBottomRight(const glm::vec2& topLeft, const glm::vec2& bottomRight)
	{
		Quad result; //!< Pre-define result
		glm::vec2 size(bottomRight.x - topLeft.x, bottomRight.y - topLeft.y); //!< Uses the coordinates to find the width and height, and put them into a "size" vec2
		return Quad::createTopLeftSize(topLeft, size); //!< Pass the top left and the size to createTopLeftSize
	}
}