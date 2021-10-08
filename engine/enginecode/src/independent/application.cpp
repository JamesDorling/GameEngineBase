/*! \file application.cpp
*/

#include "engine_pch.h"
//#include <glad/glad.h>
#include "core/application.h"
#include "events/events.h"

#ifdef NG_PLATFORM_WINDOWS
//#include "platform/windows/win32System.h"
//#else
#include "platform/GLFW/GLFWSystem.h"
#endif

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "rendering/indexBuffer.h"
#include "rendering/vertexArray.h"
#include "rendering/shader.h"
#include "rendering/subTexture.cpp"
#include "rendering/texture.h"
#include "rendering/uniformBuffer.h"

#include "renderer/renderer3D.h"
#include "renderer/renderer2D.h"
#include "renderer/renderCommands.h"

#include "camera/freeOrthographicCam.h"
#include "camera/free3DEulerCam.h"

namespace Engine {

#pragma region CLASSES
	/*! \class TPVertexNormalised
	\brief Class for normalised vertices that use the textured phong shader.
	*/
	class TPVertexNormalised
	{
	public:
		glm::vec3 m_pos; //!< Position of the vertex
		std::array<int16_t, 3> m_normal; //!< Normal of the vertex
		std::array<int16_t, 2> m_UV; //!< UV of the vertex
	
		TPVertexNormalised() : m_pos(glm::vec3(0.f)), m_normal({ 0,0,0 }), m_UV({ 0,0 }) {} //!< Default constructor
		TPVertexNormalised(const glm::vec3& pos, const std::array<int16_t, 3>& normal, const std::array<int16_t, 2>& uv) : 
			m_pos(pos), m_normal(normal), m_UV(uv) {} //!< Constructor that takes the position, normal and the UV
		static VertexBufferLayout getLayout() { return s_layout; } //!< Getter for the layout
	private:
		static VertexBufferLayout s_layout; //!< Static layout
	};
#pragma endregion

	VertexBufferLayout TPVertexNormalised::s_layout = { {{ShaderDataType::Float3, true}, {ShaderDataType::Short3, true}, {ShaderDataType::Short2, true}}, 24 }; //!< Layout for the textured phong shader

	// Set static vars
	Application* Application::s_instance = nullptr; //!< Initialise static variables

	Application::Application()
	{
		if (s_instance == nullptr)
		{
			s_instance = this; //!< Set the static variables
		}

		//Start systems

		//Start log
		m_logSystem.reset(new Log); //!< Reset the log
		m_logSystem->start(); //!< Start the log

		// Start windows system
#ifdef NG_PLATFORM_WINDOWS
//		m_windowsSystem.reset(new Win32System);
//#else
		m_windowsSystem.reset(new GLFWSystem); //!< Reset the window system
#endif
		m_windowsSystem->start(); //!< Start the window


		//Start other non-systems
		//Reset timer
		m_timer.reset(new ChronoTimer); //!< Reset the timer
		m_timer->start(); //!< start the timer


		WindowProperties props("My Game Engine", 1024, 800); //!< Create the window properties

		m_window.reset(Window::create(props)); //!< Set the window properties

		//Set handler
		//Window Events
		m_window->getEventHandler().setOnCloseCallback(std::bind(&Application::onClose, this, std::placeholders::_1)); //!< Set the on close callback
		m_window->getEventHandler().setOnResizeCallback(std::bind(&Application::onResize, this, std::placeholders::_1)); //!< Set the resize callback
		m_window->getEventHandler().setOnMovedWinCallback(std::bind(&Application::onWinMove, this, std::placeholders::_1)); //!< Set the on moved callback
		m_window->getEventHandler().setOnLostFocusCallback(std::bind(&Application::onLostFocus, this, std::placeholders::_1)); //!< Set the on window lost focus callback
		m_window->getEventHandler().setOnFocusCallback(std::bind(&Application::onFocus, this, std::placeholders::_1)); //!< Set the on window gained focus callback

		//Key Events
		m_window->getEventHandler().setOnKeyPressedCallback(std::bind(&Application::onKeyPressed, this, std::placeholders::_1)); //!< Set on key pressed callback
		m_window->getEventHandler().setOnKeyReleasedCallback(std::bind(&Application::onKeyReleased, this, std::placeholders::_1)); //!< Set on key released callback
		m_window->getEventHandler().setOnKeyTypedCallback(std::bind(&Application::onKeyTyped, this, std::placeholders::_1)); //!< Set on key typed callback

		//Mouse Events
		m_window->getEventHandler().setOnMousePressedCallback(std::bind(&Application::onMouseButtonPressed, this, std::placeholders::_1)); //!< Set on mouse button pressed callback
		m_window->getEventHandler().setOnMouseReleasedCallback(std::bind(&Application::onMouseButtonReleased, this, std::placeholders::_1)); //!< Set on mouse released callback
		m_window->getEventHandler().setOnMouseMovedCallback(std::bind(&Application::onMouseMoved, this, std::placeholders::_1)); //!< Set on mouse moved callback
		m_window->getEventHandler().setOnMouseScrolledCallback(std::bind(&Application::onMouseScrolled, this, std::placeholders::_1)); //!< Set on mouse scrolled callback

		InputPoller::setNativeWindow(m_window->getNativeWindow()); //!< Set the input poller's native window to the window in use
	}

	bool Application::onClose(WindowCloseEvent & i)
	{
		i.handle(true); //!< Handle the event
		m_running = false; //!< End the while m_running loop
		return i.handled(); //!< Return handled
	}

	bool Application::onResize(WindowResizeEvent & i)
	{
		i.handle(true); //!< Handle the event
		auto& size = i.getSize(); //!< Get the new size of the window
		//Log::info("Window Resized: ({0}, {1})", size.x, size.y);
		return i.handled(); //!< Return handled
	}

	bool Application::onWinMove(WindowMoved & i)
	{
		i.handle(true); //!< Handle the event
		auto& pos = i.getPos(); //!< Get the new position of the window
		//Log::info("Window Moved: ({0}, {1})", pos.x, pos.y);
		return i.handled(); //!< Return handled
	}

	bool Application::onLostFocus(WindowLostFocus & i)
	{
		i.handle(true); //!< Handle the event
		//Log::error("Lost Focus");
		return i.handled(); //!< Return handled
	}

	bool Application::onFocus(WindowFocus & i)
	{
		i.handle(true); //!< Handle the event
		//Log::info("Focussed");
		return i.handled(); //!< Return handled
	}

	bool Application::onKeyPressed(KeyPressed & i)
	{
		i.handle(true); //!< Handle the event
		auto keycode = i.getKeyCode(); //!< Get the keyCode
		//Log::info("Key pressed: key: {0}, repeat: {1}", i.getKeyCode(), i.getRepeatCount());
		return i.handled(); //!< Return handled
	}

	bool Application::onKeyReleased(KeyReleased & i)
	{
		i.handle(true); //!< Handle the event
		auto keycode = i.getKeyCode(); //!< Get the keyCode
	//	Log::info("Key released: key: {0}", keycode);
		return i.handled(); //!< Return handled
	}

	bool Application::onKeyTyped(KeyTyped & i)
	{
		i.handle(true); //!< Handle the event
		auto keycode = i.getKeyCode(); //!< Get the keyCode
		//Log::info("Key Typed: {0}", keycode);
		return i.handled(); //!< Return handled
	}

	bool Application::onMouseButtonPressed(MouseButtonPressed & i)
	{
		i.handle(true); //!< Handle the event
		auto mButton = i.getMouseButton(); //!< Get the mouse button
		//Log::info("Mouse Button Pressed: {0}", mButton);
		return i.handled(); //!< Return handled
	}

	bool Application::onMouseButtonReleased(MouseButtonReleased & i)
	{
		i.handle(true); //!< Handle the event
		auto mButton = i.getMouseButton(); //!< Get the mouse button
		//Log::info("Mouse Button Released: {0}", mButton);
		return i.handled(); //!< Return handled
	}

	bool Application::onMouseMoved(MouseMoved & i)
	{
		i.handle(true); //!< Handle the event
		auto mPos = i.getPos(); //!< Get the position
		//Log::info("Mouse Moved: ({0}, {1})", mPos.x, mPos.y);
		return i.handled(); //!< Return handled
	}

	bool Application::onMouseScrolled(MouseScrolled & i)
	{
		i.handle(true); //!< Handle the event
		//Log::info("Mouse Scrolled");
		return i.handled(); //!< Return handled
	}

	Application::~Application()
	{
		//Stop systems

		//Stop log
		m_logSystem->stop(); //!< Stop the log

		//Stop windows system
		m_windowsSystem->stop(); //!< Stop the window system

	}	

	std::array<int16_t, 3> normalise(const glm::vec3& norm) //!< 
	{
		std::array<int16_t, 3> result; //!< creates the result array
		if (norm.x == 1.0f) result.at(0) = INT16_MAX;										//!< If the norm is max then set it to the max of int16
		else if (norm.x == -1.0f) result.at(0) = INT16_MIN;									//!< If the norm is min set it to the min of int16
		else result.at(0) = static_cast<int16_t>(norm.x * static_cast<float>(INT16_MAX));   //!< Else convert the number to int16 via casting and multiplying it.

		if (norm.y == 1.0f) result.at(1) = INT16_MAX;										//!< If the norm is max then set it to the max of int16
		else if (norm.y == -1.0f) result.at(1) = INT16_MIN;									//!< If the norm is min set it to the min of int16
		else result.at(1) = static_cast<int16_t>(norm.y * static_cast<float>(INT16_MAX));	//!< Else convert the number to int16 via casting and multiplying it.

		if (norm.z == 1.0f) result.at(2) = INT16_MAX;										//!< If the norm is max then set it to the max of int16
		else if (norm.z == -1.0f) result.at(2) = INT16_MIN;									//!< If the norm is min set it to the min of int16
		else result.at(2) = static_cast<int16_t>(norm.z * static_cast<float>(INT16_MAX));	//!< Else convert the number to int16 via casting and multiplying it.

		return result;
	}

	std::array<int16_t, 2> normalise(const glm::vec2& uv)
	{
		std::array<int16_t, 2> result;//!< Creates the result array
		if (uv.x == 1.0f) result.at(0) = INT16_MAX;											//!< If the norm is max then set it to the max of int16
		else if (uv.x == -1.0f) result.at(0) = INT16_MIN;									//!< If the norm is min set it to the min of int16
		else result.at(0) = static_cast<int16_t>(uv.x * static_cast<float>(INT16_MAX));		//!< Else convert the number to int16 via casting and multiplying it.

		if (uv.y == 1.0f) result.at(1) = INT16_MAX;											//!< If the norm is max then set it to the max of int16
		else if (uv.y == -1.0f) result.at(1) = INT16_MIN;									//!< If the norm is min set it to the min of int16
		else result.at(1) = static_cast<int16_t>(uv.y * static_cast<float>(INT16_MAX));		//!< Else convert the number to int16 via casting and multiplying it.

		return result;
	}

	uint32_t pack(const glm::vec4& colour)
	{
		uint32_t result = 0; //!< define the result
		uint32_t R = (static_cast<uint32_t>(colour.r * 255.0f)) << 0;  //!< Turn the R value into an RGB value (0-255)
		uint32_t G = (static_cast<uint32_t>(colour.g * 255.0f)) << 8;  //!< Turn the G value into an RGB value (0-255)
		uint32_t B = (static_cast<uint32_t>(colour.b * 255.0f)) << 16; //!< Turn the B value into an RGB value (0-255)
		uint32_t A = (static_cast<uint32_t>(colour.a * 255.0f)) << 24; //!< Turn the A value into an RGB value (0-255)
		result = (R | G | B | A); //!< Put all values into result, using bitwise or
		return result; //!< return result
	}

	uint32_t pack(const glm::vec3& colour)
	{
		return pack({ colour.r, colour.g, colour.b, 1.0 }); //!< Run pack, but give the vec3 an alpha of 1
	}

	void Application::run()
	{
		

#pragma region RAW_DATA
		/*!
		Vertices of the cubes and pyramid. Normalised to be passed to the TP shader.
		*/
		std::vector<TPVertexNormalised> cubeVertices(24);
		cubeVertices.at(0) = TPVertexNormalised({ 0.5f,  0.5f, -0.5f }, normalise({ 0.f,  0.f, -1.f }), normalise({ 0.f,   0.f }));
		cubeVertices.at(1) = TPVertexNormalised({ 0.5f, -0.5f, -0.5f }, normalise({ 0.f,  0.f, -1.f }), normalise({ 0.f,   0.5f }));
		cubeVertices.at(2) = TPVertexNormalised({ -0.5f, -0.5f, -0.5f }, normalise({ 0.f,  0.f, -1.f }), normalise({ 0.33f, 0.5f }));
		cubeVertices.at(3) = TPVertexNormalised({ -0.5f,  0.5f, -0.5f }, normalise({ 0.f,  0.f, -1.f }), normalise({ 0.33f, 0.f }));
		cubeVertices.at(4) = TPVertexNormalised({ -0.5f, -0.5f,  0.5f }, normalise({ 0.f,  0.f,  1.f }), normalise({ 0.33f, 0.5f }));
		cubeVertices.at(5) = TPVertexNormalised({ 0.5f, -0.5f,  0.5f }, normalise({ 0.f,  0.f,  1.f }), normalise({ 0.66f, 0.5f }));
		cubeVertices.at(6) = TPVertexNormalised({ 0.5f,  0.5f,  0.5f }, normalise({ 0.f,  0.f,  1.f }), normalise({ 0.66f, 0.f }));
		cubeVertices.at(7) = TPVertexNormalised({ -0.5f,  0.5f,  0.5f }, normalise({ 0.f,  0.f,  1.f }), normalise({ 0.33,  0.f }));
		cubeVertices.at(8) = TPVertexNormalised({ -0.5f, -0.5f, -0.5f }, normalise({ 0.f, -1.f,  0.f }), normalise({ 1.f,   0.f }));
		cubeVertices.at(9) = TPVertexNormalised({ 0.5f, -0.5f, -0.5f }, normalise({ 0.f, -1.f,  0.f }), normalise({ 0.66f, 0.f }));
		cubeVertices.at(10) = TPVertexNormalised({ 0.5f, -0.5f,  0.5f }, normalise({ 0.f, -1.f,  0.f }), normalise({ 0.66f, 0.5f }));
		cubeVertices.at(11) = TPVertexNormalised({ -0.5f, -0.5f,  0.5f }, normalise({ 0.f, -1.f,  0.f }), normalise({ 1.0f,  0.5f }));
		cubeVertices.at(12) = TPVertexNormalised({ 0.5f,  0.5f,  0.5f }, normalise({ 0.f,  1.f,  0.f }), normalise({ 0.f,   0.5f }));
		cubeVertices.at(13) = TPVertexNormalised({ 0.5f,  0.5f, -0.5f }, normalise({ 0.f,  1.f,  0.f }), normalise({ 0.f,   1.0f }));
		cubeVertices.at(14) = TPVertexNormalised({ -0.5f,  0.5f, -0.5f }, normalise({ 0.f,  1.f,  0.f }), normalise({ 0.33f, 1.0f }));
		cubeVertices.at(15) = TPVertexNormalised({ -0.5f,  0.5f,  0.5f }, normalise({ 0.f,  1.f,  0.f }), normalise({ 0.3f,  0.5f }));
		cubeVertices.at(16) = TPVertexNormalised({ -0.5f,  0.5f,  0.5f }, normalise({ -1.f,  0.f,  0.f }), normalise({ 0.66f, 0.5f }));
		cubeVertices.at(17) = TPVertexNormalised({ -0.5f,  0.5f, -0.5f }, normalise({ -1.f,  0.f,  0.f }), normalise({ 0.33f, 0.5f }));
		cubeVertices.at(18) = TPVertexNormalised({ -0.5f, -0.5f, -0.5f }, normalise({ -1.f,  0.f,  0.f }), normalise({ 0.33f, 1.0f }));
		cubeVertices.at(19) = TPVertexNormalised({ -0.5f, -0.5f,  0.5f }, normalise({ -1.f,  0.f,  0.f }), normalise({ 0.66f, 1.0f }));
		cubeVertices.at(20) = TPVertexNormalised({ 0.5f, -0.5f, -0.5f }, normalise({ 1.f,  0.f,  0.f }), normalise({ 1.0f,  1.0f }));
		cubeVertices.at(21) = TPVertexNormalised({ 0.5f,  0.5f, -0.5f }, normalise({ 1.f,  0.f,  0.f }), normalise({ 1.0f,  0.5f }));
		cubeVertices.at(22) = TPVertexNormalised({ 0.5f,  0.5f,  0.5f }, normalise({ 1.f,  0.f,  0.f }), normalise({ 0.66f, 0.5f }));
		cubeVertices.at(23) = TPVertexNormalised({ 0.5f, -0.5f,  0.5f }, normalise({ 1.f,  0.f,  0.f }), normalise({ 0.66f, 1.0f }));

		std::vector<TPVertexNormalised> pyramidVertices(16);
		pyramidVertices.at(0) = TPVertexNormalised({ -0.5f, -0.5f, -0.5f }, normalise({ 0.f, -1.f, 0.f }), normalise({ 0.f, 0.f }));
		pyramidVertices.at(1) = TPVertexNormalised({ 0.5f, -0.5f, -0.5f }, normalise({ 0.f, -1.f, 0.f }), normalise({ 0.f, 0.f }));
		pyramidVertices.at(2) = TPVertexNormalised({ 0.5f, -0.5f,  0.5f }, normalise({ 0.f, -1.f, 0.f }), normalise({ 0.f, 0.f }));
		pyramidVertices.at(3) = TPVertexNormalised({ -0.5f, -0.5f,  0.5f }, normalise({ 0.f, -1.f, 0.f }), normalise({ 0.f, 0.f }));

		pyramidVertices.at(4) = TPVertexNormalised({ -0.5f, -0.5f, -0.5f }, normalise({ -0.8944f, 0.4472f, 0.f }), normalise({ 0.f, 0.f }));
		pyramidVertices.at(5) = TPVertexNormalised({ -0.5f, -0.5f,  0.5f }, normalise({ -0.8944f, 0.4472f, 0.f }), normalise({ 0.f, 0.f }));
		pyramidVertices.at(6) = TPVertexNormalised({ 0.0f,  0.5f,  0.0f }, normalise({ -0.8944f, 0.4472f, 0.f }), normalise({ 0.f, 0.f }));

		pyramidVertices.at(7) = TPVertexNormalised({ -0.5f, -0.5f,  0.5f }, normalise({ 0.f, 0.4472f, 0.8944f }), normalise({ 0.f, 0.f }));
		pyramidVertices.at(8) = TPVertexNormalised({ 0.5f, -0.5f,  0.5f }, normalise({ 0.f, 0.4472f, 0.8944f }), normalise({ 0.f, 0.f }));
		pyramidVertices.at(9) = TPVertexNormalised({ 0.0f,  0.5f,  0.0f }, normalise({ 0.f, 0.4472f, 0.8944f }), normalise({ 0.f, 0.f }));

		pyramidVertices.at(10) = TPVertexNormalised({ 0.5f, -0.5f,  0.5f }, normalise({ 0.8944f, 0.4472f, 0.f }), normalise({ 0.f, 0.f }));
		pyramidVertices.at(11) = TPVertexNormalised({ 0.5f, -0.5f, -0.5f }, normalise({ 0.8944f, 0.4472f, 0.f }), normalise({ 0.f, 0.f }));
		pyramidVertices.at(12) = TPVertexNormalised({ 0.0f,  0.5f,  0.0f }, normalise({ 0.8944f, 0.4472f, 0.f }), normalise({ 0.f, 0.f }));

		pyramidVertices.at(13) = TPVertexNormalised({ 0.5f, -0.5f, -0.5f }, normalise({ 0.f, 0.4472f, -0.8944f }), normalise({ 0.f, 0.f }));
		pyramidVertices.at(14) = TPVertexNormalised({ -0.5f, -0.5f, -0.5f }, normalise({ 0.f, 0.4472f, -0.8944f }), normalise({ 0.f, 0.f }));
		pyramidVertices.at(15) = TPVertexNormalised({ 0.0f,  0.5f,  0.0f }, normalise({ 0.f, 0.4472f, -0.8944f }), normalise({ 0.f, 0.f }));

		uint32_t pyramidIndices[3 * 6] =
		{
			0, 1, 2,
			2, 3, 0,
			4, 5, 6,
			7, 8, 9,
			10, 11, 12,
			13, 14, 15
		};

		uint32_t cubeIndices[3 * 12] = {
			0, 1, 2,
			2, 3, 0,
			4, 5, 6,
			6, 7, 4,
			8, 9, 10,
			10, 11, 8,
			12, 13, 14,
			14, 15, 12,
			16, 17, 18,
			18, 19, 16,
			20, 21, 22,
			22, 23, 20
		};
#pragma endregion

#pragma region TEXTURES

		std::shared_ptr<Texture> letterTexture; //!< Pointer to a texture
		letterTexture.reset(Texture::create("../sandbox/assets/textures/letterCube.png")); //!< puts the pointer on the lettercube texture
		std::shared_ptr<Texture> numberTexture; //!< Pointer to a texture
		numberTexture.reset(Texture::create("../sandbox/assets/textures/numberCube.png")); //!< Puts the pointer on the numbercube texture
		unsigned char whitePix[4] = { 255, 255, 255, 255 }; //!< Default white pixel, for the pyramid
		std::shared_ptr<Texture> pyrTexture; //!< Pyramid texture pointer
		pyrTexture.reset(Texture::create(1, 1, 4, whitePix)); //!< Creates the texture for the pyramid out of the white pixel


		//SubTexture letterCube(letterTexture, { 0.f, 0.f }, { 1.f, 0.5f });
		//SubTexture numberCube(numberTexture, { 0.f, 0.5f }, { 1.f, 1.f });
#pragma endregion

#pragma region GL_BUFFERS
		std::shared_ptr<VertexArray> cubeVAO; //!< Cube vertex array
		std::shared_ptr<VertexBuffer> cubeVBO; //!< Cube vertex buffer
		std::shared_ptr<IndexBuffer> cubeIBO; //!< Cube index buffer

		cubeVAO.reset(VertexArray::create()); //!< Reset the cube vertex array pointer

		cubeVBO.reset(VertexBuffer::create(cubeVertices.data(), sizeof(TPVertexNormalised) * cubeVertices.size(), TPVertexNormalised::getLayout())); //!< Reset the vertex buffer pointer

		cubeIBO.reset(IndexBuffer::create(cubeIndices, 36)); //!< Reset the index buffer pointer

		cubeVAO->addVertexBuffer(cubeVBO); //!< Add the vertex array to the vertex buffer
		cubeVAO->setIndexBuffer(cubeIBO); //!< Add the index buffer to the vertex buffer


		std::shared_ptr<VertexArray> pyramidVAO; //!< Pyramid's vertex array
		std::shared_ptr<VertexBuffer> pyramidVBO; //!< Pyramid's vertex buffer
		std::shared_ptr<IndexBuffer> pyramidIBO; //!< Pyramids index buffer

		pyramidVAO.reset(VertexArray::create()); //!< Reset the pyramid vertex array buffer

		pyramidVBO.reset(VertexBuffer::create(pyramidVertices.data(), sizeof(TPVertexNormalised) * pyramidVertices.size(), TPVertexNormalised::getLayout())); //!< Reset the vertex buffer

		pyramidIBO.reset(IndexBuffer::create(pyramidIndices, 18)); //!< reset the pyramid index buffer

		pyramidVAO->addVertexBuffer(pyramidVBO); //!< Add the vertex buffer to the vertex array
		pyramidVAO->setIndexBuffer(pyramidIBO); //!< Add the index buffer to the vertex array
#pragma endregion

#pragma region SHADER
		std::shared_ptr<Shader> TPShader; //!< Pointer to the textured phong shader
		TPShader.reset(Shader::create("../sandbox/assets/shaders/texturedPhong.glsl")); //!< Reset the shader, give it the texturedPhong.glsl file
#pragma endregion 

#pragma region MATERIALS

		std::shared_ptr<Material> pyramidMat; //!< Pyramid material pointer
		std::shared_ptr<Material> letterMat; //!< Lettercube material pointer
		std::shared_ptr<Material> numberMat; //!< Numbercube material pointer

		pyramidMat.reset(new Material(TPShader, { 0.0f, 1.0f, 0.0f, 0.0f })); //!< Reset pointer with blank green material
		letterMat.reset(new Material(TPShader, letterTexture));	 //!< Reset pointer with lettercube material
		numberMat.reset(new Material(TPShader, numberTexture));  //!< Reset pointer with numbercube material

		SceneWideUniform swu3D; //!< 3D Cam's scene wide uniforms

		SceneWideUniform swu2D; //!< 2D Cam's scene wide uniform

#pragma endregion

		glm::mat4 view = glm::lookAt(
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(0.f, 1.f, 0.f)
		); //!< view, for use in cameras
		glm::mat4 projection = glm::perspective(glm::radians(45.f), 1024.f / 800.f, 0.1f, 100.f); //!< Projection, for use in cameras

		Free2DOrthographicCam Cam2D(0.f, static_cast<float>(m_window->getWidth()), static_cast<float>(m_window->getHeight()), 0.f); //!< Cam2D constructor call, given the far left, the far right, the bottom then the top.
		Free3DEulerCam Cam3D(45.f, static_cast<float>(m_window->getWidth()/m_window->getHeight()), 0.1f, 100.f);//!< Cam3D constructor call, given the FOV, the aspect ratio, a near distance and a far distance

		//Cam UBO
		uint32_t blockNo = 0; //!< Block number, used to seperate the UBOs
		UniformBufferLayout camLayout = { { "u_projection", ShaderDataType::Mat4 }, { "u_view", ShaderDataType::Mat4 } }; //!< Cam layout, provides the two types of data we are passing to the shader

		std::shared_ptr<UniformBuffer> cam2DUBO;		  //!< Pointer to Cam2D ubo
		cam2DUBO.reset(UniformBuffer::create(camLayout)); //!< Reset cam2dUBO pointer, give it the cam layout

		cam2DUBO->attachShaderBlock(TPShader, "b_camera"); //!< Attach cam2dUBO to the b_camera block in quad1 shader
		//cam2DUBO->uploadShaderData("u_projection", glm::value_ptr(projection));
		//cam2DUBO->uploadShaderData("u_view", glm::value_ptr(view));
		
		std::shared_ptr<UniformBuffer> cam3DUBO;			//!< Pointer to Cam3Dubo
		cam3DUBO.reset(UniformBuffer::create(camLayout));	//!< Reset cam2dUBO pointer, give it the cam layout

		cam3DUBO->attachShaderBlock(TPShader, "b_camera");
		//cam3DUBO->uploadShaderData("u_projection", glm::value_ptr(projection));
		//cam3DUBO->uploadShaderData("u_view", glm::value_ptr(view));

		blockNo++; //!< Increment the block number

		glm::vec3 lightColour(1.f, 1.f, 1.f); //!< Light colour is white
		glm::vec3 lightPos   (1.f, 4.f, 6.f); //!< Position is above the cubes
		glm::vec3 viewPos    (0.f, 0.f, 0.f); //!< View position is the camera position, 0,0,0

		//Light UBO
		UniformBufferLayout lightLayout{ {"u_lightPos", ShaderDataType::Float3}, {"u_viewPos", ShaderDataType::Float3}, {"u_lightColour", ShaderDataType::Float3} }; //!< Light layout
		std::shared_ptr<UniformBuffer> lightUBO; //!< Pointer to the light UBO
		lightUBO.reset(UniformBuffer::create(lightLayout)); //!< Reset the uniform buffer with the light layout
		//uint32_t lightDataSize = sizeof(glm::vec3) * 3; //Doesnt seem to use this

		lightUBO->attachShaderBlock(TPShader, "b_light"); //!< Attaches the lightUBO to the b_light uniform layout of TPShader

		lightUBO->uploadShaderData("u_lightPos", glm::value_ptr(lightPos)); //!< upload the light position
		lightUBO->uploadShaderData("u_viewPos", glm::value_ptr(viewPos)); //!< Upload the view positiion
		lightUBO->uploadShaderData("u_lightColour", glm::value_ptr(lightColour)); //!< upload the light colour

		glm::mat4 models[3];
		models[0] = glm::translate(glm::mat4(1.0f), glm::vec3(-2.f, 0.f, -6.f)); //!< Model 1, model and translate used interchangeeably
		models[1] = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, -6.f)); //!< Model 2
		models[2] = glm::translate(glm::mat4(1.0f), glm::vec3(2.f, 0.f, -6.f)); //!< Model 3

		float timestep = 0.f; //!< Timestep initialiser

		Quad rectangles[6];
		rectangles[0] = Quad::createCentreHalfExtend({ 0.f, 50.f }, { 50.f, 10.f }); //!< Creates a square from the top left , with the half extents of 50, 10
		rectangles[1] = Quad::createTopLeftBottomRight({ 600.f, 100.f }, { 350.f, 105.f }); //!< Creates a square with the top left coordinate and bottom right coordinate
		rectangles[2] = Quad::createTopLeftSize({ 300.f, 300.f }, { 50.f, 10.f }); //!< Creates a square using the top left and the side sizes
		rectangles[3] = Quad::createCentreHalfExtend({ 500.f, 600.f }, 50.f); //!< Creates a square from the top left , with the half extents of 50, 10
		rectangles[4] = Quad::createTopLeftBottomRight({ 600.f, 500.f }, { 450.f, 405.f }); //!< Creates a square with the top left coordinate and bottom right coordinate
		rectangles[5] = Quad::createTopLeftSize({ 300.f, 600.f }, 150.f); //!< Creates a square using the lop left coordinates and side sizes




		//glm::vec3 matLightData[3] = { { 1.0f, 1.0f, 1.0f }, { -2.0f, 4.0f, 6.0f }, { 0.0f, 0.0f, 0.0f } };
		swu3D["b_camera"] = cam3DUBO; //!< assigns the scenewide uniform "b_camera" block to be cam3dUBO
		swu3D["b_light"] = lightUBO; //!< assigns the scenewide uniform "b_light" block to be LightUBO

		swu2D["b_camera"] = cam2DUBO; //!< Assigns the scenewide uniform "b_camera" to be cam2DUBO

		Renderer3D::init(); //!< Initialises the 3D renderer
		Renderer2D::init(); //!< Initialises the 2D renderer

			

		float advance; //!< Advance will be used later
		while (m_running)
		{
			timestep = m_timer->getElapsedTime(); //!< Timestep
			m_timer->reset(); //!< Reset the timer pointer
			//Log::trace("FPS {0}", 1.0f / timestep);
			//if (InputPoller::isKeyPressed(NG_KEY_W)) Log::error("W Pressed");
			//if (InputPoller::isMouseButtonPressed(NG_MOUSE_BUTTON_1)) Log::error("Left Mouse Button Pressed");
			//Log::trace("Current mouse pos: ({0}, {1})", InputPoller::getMouseX(), InputPoller::getMouseY());
			RendererCommon::actionCommand(RenderCommand::setBackfaceCullingCommand(true)); //!< Set the backface culling

			RendererCommon::actionCommand(RenderCommand::clearDepthColourCommand()); //!< Clear the depth buffer and the colour buffer

			RendererCommon::actionCommand(RenderCommand::setClearColourCommand(1.f, 0.f, 1.f, 1.f)); //!< Set the clear colour 

			for (auto& model : models) { model = glm::rotate(model, timestep, glm::vec3(0.3f, 1.f, 0.f)); } //!< Rotate all of the models

			cam3DUBO->uploadShaderData("u_projection", glm::value_ptr(Cam3D.getCamera().projection)); //!< Upload the 3D projection to cam3DUBO
			cam3DUBO->uploadShaderData("u_view", glm::value_ptr(Cam3D.getCamera().view)); //!< Upload the 3D view to Cam3DUBO

			RendererCommon::actionCommand(RenderCommand::setDepthTestCommand(true)); //!< Set the depth testing to true

			Renderer3D::begin(swu3D); //!< begin the 3D renderer

			Renderer3D::submit(pyramidVAO, pyramidMat, models[0]); //!< submit the pyramid vertex array, material and model
			Renderer3D::submit(cubeVAO, letterMat, models[1]); //!< submit the cube vertex array, material and model
			Renderer3D::submit(cubeVAO, numberMat, models[2]); //!< submit the cube vertex array, material and model

			Renderer3D::end(); //!< End the 3D renderer

			RendererCommon::actionCommand(RenderCommand::setDepthTestCommand(false)); //!< Turn off the depth testing
			RendererCommon::actionCommand(RenderCommand::setBlendCommand(true)); //!< Set blending to true

			cam2DUBO->uploadShaderData("u_projection", glm::value_ptr(Cam2D.getCamera().projection)); //!< Upload the 2D projection to Cam2DUBO
			cam2DUBO->uploadShaderData("u_view", glm::value_ptr(Cam2D.getCamera().view)); //!< Upload the 2D view to Cam2DUBO
			

			Renderer2D::begin(swu2D); //!< Begin the 2D renderer

			Renderer2D::submit(rectangles[0], { 0.0f, 1.0f, 0.0f, 1.0f });										 //!< submit the first rectangle
			Renderer2D::submit(rectangles[1], letterTexture);													 //!< submit the second rectangle
			Renderer2D::submit(rectangles[2], { 0.0f, 1.0f, 1.0f, 1.0f }, numberTexture);						 //!< submit the third rectangle
			Renderer2D::submit(rectangles[3], { 0.0f, 1.0f, 1.0f, 0.5f }, letterTexture, 45.f, true);			 //!< submit the fourth rectangle
			Renderer2D::submit(rectangles[4], letterTexture, 45.f, true);										 //!< submit the fifth rectangle
			Renderer2D::submit(rectangles[5], { 0.0f, 1.0f, 1.0f, 1.0f }, glm::radians(45.f));					 //!< submit the sixth rectangle
			uint32_t x = 50.f;																					 //!< Sets the base advance to 50.f
			Renderer2D::submit('H', glm::vec2(x, 550.f), advance, glm::vec4(1.f, 1.f, 1.f, 1.f)); x += advance;	 //!< submit the character 'H'
			Renderer2D::submit('o', glm::vec2(x, 550.f), advance, glm::vec4(0.f, 1.f, 1.f, 1.f)); x += advance;	 //!< submit the character 'o'
			Renderer2D::submit('w', glm::vec2(x, 550.f), advance, glm::vec4(1.f, 0.5f, 1.f, 1.f)); x += advance; //!< submit the character 'w'
			Renderer2D::submit(' ', glm::vec2(x, 550.f), advance, glm::vec4(1.f, 1.f, 0.f, 1.f)); x += advance;	 //!< submit the character ' '
			Renderer2D::submit('y', glm::vec2(x, 550.f), advance, glm::vec4(0.f, 1.f, 1.f, 1.f)); x += advance;	 //!< submit the character 'y'
			Renderer2D::submit('o', glm::vec2(x, 550.f), advance, glm::vec4(1.f, 0.5f, 1.f, 1.f)); x += advance; //!< submit the character 'o'
			Renderer2D::submit('u', glm::vec2(x, 550.f), advance, glm::vec4(1.f, 1.f, 0.f, 1.f)); x += advance;	 //!< submit the character 'u'
			Renderer2D::submit(' ', glm::vec2(x, 550.f), advance, glm::vec4(0.f, 1.f, 1.f, 1.f)); x += advance;	 //!< submit the character ' '
			Renderer2D::submit("going?", glm::vec2(x, 550.f), glm::vec4(0.f, 0.f, 1.f, 1.f));					 //!< submit the string "going?"


			Renderer2D::end(); //!< End the 2D renderer

			RendererCommon::actionCommand(RenderCommand::setBlendCommand(false)); //!< Turn off the blend command

			Cam2D.onUpdate(timestep); //!< Update cam2D
			Cam3D.onUpdate(timestep); //!< Update cam3D


			m_window->onUpdate(timestep); //!< Update the window
		}
	}
}