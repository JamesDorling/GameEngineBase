/*! \file freeOrthographicCam.cpp */
#include "engine_pch.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "camera/freeOrthographicCam.h"
#include "events/codes.h"
#include "core/inputPoller.h"

namespace Engine
{
	Free2DOrthographicCam::Free2DOrthographicCam(float left, float right, float top, float bottom)
	{
		m_camera.projection = glm::ortho(left, right, top, bottom); //Top and bottom are technically inverted, but thats because down in Y is + in Y
		m_camera.view = glm::mat4(1.f);
	}

	void Free2DOrthographicCam::onUpdate(float t)
	{
		if (InputPoller::isKeyPressed(NG_KEY_W)) //!< Moves the camera up
		{
			m_pos.x += -sin(glm::radians(m_rotation)) * m_translationSpeed * t;
			m_pos.y +=  cos(glm::radians(m_rotation)) * m_translationSpeed * t;
		}

		if (InputPoller::isKeyPressed(NG_KEY_A)) //!< Moves the camera left
		{
			m_pos.x += cos(glm::radians(m_rotation)) * m_translationSpeed * t;
			m_pos.y += sin(glm::radians(m_rotation)) * m_translationSpeed * t;
		}

		if (InputPoller::isKeyPressed(NG_KEY_S)) //!< Moves the camera down
		{
			m_pos.x -= -sin(glm::radians(m_rotation)) * m_translationSpeed * t;
			m_pos.y -= cos(glm::radians(m_rotation)) * m_translationSpeed * t;
		}

		if (InputPoller::isKeyPressed(NG_KEY_D)) //!< Moves the camera right
		{
			m_pos.x -= cos(glm::radians(m_rotation)) * m_translationSpeed * t;
			m_pos.y -+ sin(glm::radians(m_rotation)) * m_translationSpeed * t;
		}

		glm::mat4 translate = glm::translate(glm::mat4(1.f), glm::vec3(m_pos.x, m_pos. y, 1.f)); //!< gets the current position of the camera plus the movement that the player has done
		glm::mat4 rotate = glm::rotate(glm::mat4(1.f), m_rotation, { 0.0f, 0.0f, 1.0f }); //!< Gets the current rotation of the camera plus the movement that the player has done
		m_camera.view = glm::inverse(translate * rotate); //!< changes the camera's view using the position and the rotation
	}
}