/*! \class free3DEulerCam.cpp */
#include "engine_pch.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "camera/free3DEulerCam.h"
#include "events/codes.h"
#include "core/inputPoller.h"

namespace Engine
{
	Free3DEulerCam::Free3DEulerCam(float fov, float aspect, float near, float far)
	{
		m_camera.projection = glm::perspective(fov, aspect, near, far); //!< sets the projection of the camera using glm:: perspective
		m_camera.view = glm::mat3(1.f); //!< Sets the view to a mat3 of 1s
		m_lastMousePosition = InputPoller::getMousePosition(); //!< Gets the mouse position and sets it to the last mouse position
	}

	void Free3DEulerCam::onUpdate(float t)
	{
		glm::vec3 right = { m_transform[0][0], m_transform[0][1], m_transform[0][2] }; //!< Assigns the right transform to a vec3
		glm::vec3 forward = { -m_transform[2][0], -m_transform[2][1], -m_transform[2][2] }; //!< Assigns the forward transform to a vec3

		if (InputPoller::isKeyPressed(NG_KEY_W)) m_pos += (forward * m_translationSpeed * t); //!< Camera controls using WASD to move the camera in the cardinal directions
		if (InputPoller::isKeyPressed(NG_KEY_A)) m_pos -=   (right * m_translationSpeed * t); 
		if (InputPoller::isKeyPressed(NG_KEY_S)) m_pos -= (forward * m_translationSpeed * t); 
		if (InputPoller::isKeyPressed(NG_KEY_D)) m_pos +=   (right * m_translationSpeed * t); 

		if (InputPoller::isKeyPressed(NG_KEY_UP))    m_rotationX += (m_translationSpeed * t); //!< Camera rotation controls
		if (InputPoller::isKeyPressed(NG_KEY_LEFT))  m_rotationY += (m_translationSpeed * t);
		if (InputPoller::isKeyPressed(NG_KEY_DOWN))  m_rotationX -= (m_translationSpeed * t);
		if (InputPoller::isKeyPressed(NG_KEY_RIGHT)) m_rotationY -= (m_translationSpeed * t);
		if (InputPoller::isKeyPressed(NG_KEY_E))     m_rotationZ += (m_translationSpeed * t);
		if (InputPoller::isKeyPressed(NG_KEY_Q))     m_rotationZ -= (m_translationSpeed * t);


		glm::vec2 currentMousePos = InputPoller::getMousePosition(); //!< Sets the current mouse position
		glm::vec2 deltaMousePos = currentMousePos - m_lastMousePosition; //!< Gets the direction the mouse has moved in
		deltaMousePos /= glm::vec2(800.f, 600.f); //!< Divides the mouse movement direction by the aspect ratio of the window

		m_rotationY -= m_sensitivity * deltaMousePos.x * t; //!< Uses the mouse direction and the sensitivity to define the rotation
		m_rotationX -= m_sensitivity * deltaMousePos.y * t;	//!< Uses the mouse direction and the sensitivity to define the rotation

		m_lastMousePosition = currentMousePos; //!< Sets the new last mouse position

		glm::mat4 rotX = glm::rotate(glm::mat4(1.f), m_rotationX, glm::vec3(1.f, 0.f, 0.f)); //!< Transforms the rotation floats into matrices
		glm::mat4 rotY = glm::rotate(glm::mat4(1.f), m_rotationY, glm::vec3(0.f, 1.f, 0.f)); //!< Transforms the rotation floats into matrices
		glm::mat4 rotZ = glm::rotate(glm::mat4(1.f), m_rotationZ, glm::vec3(0.f, 0.f, 1.f)); //!< Transforms the rotation floats into matrices

		m_orientation = rotX * rotY * rotZ; //!< Sets the orientation usint the rotation matrices

		m_transform = glm::translate(glm::mat4(1.f), m_pos) * m_orientation; //!< Defines transform

		m_camera.view = inverse(m_transform); //!< Changes the view according to the transform

	}


}
