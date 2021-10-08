/*! \file renderer3D */
#pragma once

#include "renderer/rendererCommon.h"

namespace Engine
{
	/*! \class Material
	* \brief Class for rendering a material (Shader and the shader's uniform data)
	*/
	class Material
	{
	public:
		Material(const std::shared_ptr<Shader>& shader) : m_shader(shader), m_flag(0), m_texture(nullptr), m_tint(glm::vec4(0)) 
		{}
		Material(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture, const glm::vec4& tint) : m_shader(shader), m_texture(texture), m_tint(tint) 
		{
			setFlag(flag_texture | flag_tint); //!< Set both flags
		}
		Material(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture) : m_shader(shader), m_texture(texture), m_tint(glm::vec4(0))
		{
			setFlag(flag_texture); //!< Set both flags
		}
		Material(const std::shared_ptr<Shader>& shader, const glm::vec4& tint) : m_shader(shader), m_tint(tint)
		{
			setFlag(flag_tint); //!< Set both flags
		}

		inline std::shared_ptr<Shader> getShader() const { return m_shader; } //!< Getter for the shader
		inline std::shared_ptr<Texture> getTexture() const { return m_texture; } //!< Getter for the texture
		inline glm::vec4 getTint() const { return m_tint; } //!< Getter for the tint
		bool isFlagSet(uint32_t flag) const { return m_flag & flag; } //!< Bool to check if flag is set (Is set if it isnt a 0)

		// No setter for the shader, need to make a new material to change the shader.
		void setTexture(const std::shared_ptr<Texture>& texture) { m_texture = texture; } //!< Setter for the texture
		void setTint(const glm::vec4 tint) { m_tint = tint; } //!< Setter for the tint

		constexpr static uint32_t flag_texture = 1 << 0; //!< 00000001
		constexpr static uint32_t flag_tint = 1 << 1; //!< 00000010
	private:
		uint32_t m_flag = 0; //!< Bitfield representation of shader settings
		std::shared_ptr<Shader> m_shader; //!< The material's shader
		std::shared_ptr<Texture> m_texture; //!< The material's texture
		glm::vec4 m_tint; //!< Colour tint to be applied to the geometry
		void setFlag(uint32_t flag) { m_flag = m_flag | flag; } //!< Setter for the flag
	};

	/*! \class Renderer3D
	* \brief Class for rendering unbatched 3D geometry
	*/
	class Renderer3D
	{
	public:
		static void init(); //!< Initialise the renderer
		static void begin(const SceneWideUniform& sceneWideUniform); //!< Begin a new 3D scene
		static void submit(const std::shared_ptr<VertexArray>& geometry, const std::shared_ptr<Material>& material, const glm::mat4& model); //!< Submit some geometry to be rendered
		static void end(); //!< End the current 3D scene
	private:
		struct InternalData
		{
			SceneWideUniform sceneWideUniform; //!< Replace with a UBO
			std::shared_ptr<Texture> defaultTexture; //!< Empty texture for default
			glm::vec4 defaultTint; //!< Plain white tint for default
		};

		static std::shared_ptr<InternalData> s_data; //!< Renderer's internal data
	};
}
