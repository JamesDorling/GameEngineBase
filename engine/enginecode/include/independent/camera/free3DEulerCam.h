/*! \file free3DEulercam.h */
#pragma once

#include "camera.h"

namespace Engine
{
	/*! \class Free3DEulerCam */
	class Free3DEulerCam : public CameraController
	{
	public:
		Free3DEulerCam(float fov, float aspect, float near, float far); //!< Contructor, takes 4 floats.
		virtual void onUpdate(float t) override; //!< Onupdate override for this camera
	private:
		float m_rotationSpeed = 1.f; //!< Speed of rotation
		float m_rotationX = 0.f; //!< xRotation
		float m_rotationY = 0.f; //!< yRotation
		float m_rotationZ = 0.f; //!< zRotation
		float m_translationSpeed = 2.f; //!< Translation speed

		float m_sensitivity = 20.f; //!< Camera movement sensitivity

		glm::vec2 m_lastMousePosition = {0.f, 0.f}; //!< last position of the mouse
		glm::mat4 m_transform; //!< transform, used to move the camera

		glm::mat4 m_orientation; //!< Orientation, used to set the orientation
	};
}
