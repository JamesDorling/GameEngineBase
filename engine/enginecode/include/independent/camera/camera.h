/*! \file camera.h*/
#pragma once
#include "events/event.h"
#include <glm/glm.hpp>

namespace Engine
{
	/*! \class Camera
	*/
	class Camera
	{
	public:
		glm::mat4 view; //!< View
		glm::mat4 projection; //!< Projection
		void updateView(const glm::mat4& transform) //!< updates the view every frame, moving the camera
		{
			view = glm::inverse(transform); //!< Changes the view by the inverse of transform.
		}
	};

	/*! \class CameraController
	\brief base class for a camera controller
	*/
	class CameraController
	{
	public:
		Camera& getCamera() { return m_camera; } //!< Getter for the camera
		virtual void onUpdate(float t) {} //!< Update, to be called in the while m_running loop in application
		virtual void onEvent(Event& e) {} //!< On event, for when an event happens

	protected:
		Camera m_camera; //!< Camera
		glm::vec3 m_pos = { 0.f, 0.f, 0.f }; //!< Position
	};
}