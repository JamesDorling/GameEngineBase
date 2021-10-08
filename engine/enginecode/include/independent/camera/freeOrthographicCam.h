/*! \file freeOrthographicCam */
#pragma once

#include "camera.h"

namespace Engine
{
	/*! \class Free2DOrthographicCam */
	class Free2DOrthographicCam : public CameraController
	{
	public:
		Free2DOrthographicCam(float left, float right, float top, float bottom); //!< Constructor, takes 4 floats
		virtual void onUpdate(float t) override; //!< On update override, called in application while running loop
	private:
		float m_rotation = 0.f; //!< Rotation
		float m_translationSpeed = 40.f; //!< Translation speed
	};
}