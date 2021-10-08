/*! \file renderer3D.cpp */
#include "engine_pch.h"
#include <glad/glad.h>
#include "renderer/renderer3D.h"
#include "rendering/uniformBuffer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace Engine
{
	std::shared_ptr<Renderer3D::InternalData> Renderer3D::s_data = nullptr;

	void Renderer3D::init()
	{
		s_data.reset(new InternalData); //!< Reset s_data's internal data
		unsigned char whitePix[4] = { 255, 255, 255, 255 }; //!< Define a white pixel
		s_data->defaultTexture.reset(Texture::create(1, 1, 4, whitePix)); //!< Create a white texture for the default

		s_data->defaultTint = { 1.f, 1.f, 1.f, 1.f }; //!< Set the default tint as blank
	}

	void Renderer3D::begin(const SceneWideUniform & sceneWideUniform)
	{
		s_data->sceneWideUniform = sceneWideUniform; //!< Set s_data's scene wide uniforms
	}

	void Renderer3D::submit(const std::shared_ptr<VertexArray>& geometry, const std::shared_ptr<Material>& material, const glm::mat4 & model)
	{
		//Bind shader
		glUseProgram(material->getShader()->getRenderID()); //!< Bind the shader
		//Could be made API agnostic via abstraction

		//Apply scenewideuniform
		for (auto& dataPair : s_data->sceneWideUniform) //!< Goes through the scenewide uniforms and attaches them to the shader
		{
			const char* nameOfUniform = dataPair.first;
			dataPair.second->attachShaderBlock(material->getShader(), nameOfUniform);
		}

		//apply material uniforms (per draw uniforms)
		material->getShader()->uploadMat4("u_model", model); //!< uploads the model

		//texture
		if (material->isFlagSet(Material::flag_texture)) //!< If the flag is set, there is a material
		{
			glBindTexture(GL_TEXTURE_2D, material->getTexture()->getRenderID()); //!< Bind the texture if there is one
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, s_data->defaultTexture->getRenderID()); //!< Bind the default texture if there isnt one
		}
		material->getShader()->uploadInt("u_texData", 0); //!< Uploads the texdata


		//tint
		if (material->isFlagSet(Material::flag_tint)) //!< If the flag is set, there is a tint
		{
			material->getShader()->uploadFloat4("u_tint", material->getTint()); //!< Upload the tint if there is one
		}
		else
		{
			material->getShader()->uploadFloat4("u_tint", s_data->defaultTint); //!< Upload the default tint if there isnt one
		}

		//bind geometry (vao and ibo)
		glBindVertexArray(geometry->getRenderID()); //!< Bind the vertex array
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->getIndexBuffer()->getRenderID()); //!< bind the index buffer

		//submit the draw call
		glDrawElements(GL_TRIANGLES, geometry->getDrawCount(), GL_UNSIGNED_INT, nullptr); //!< Draw the submitted object
	}

	void Renderer3D::end()
	{
		s_data->sceneWideUniform.clear(); //!< Clear the scene wide uniforms
	}
}