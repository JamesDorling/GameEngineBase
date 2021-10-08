/*! \file timer.h */
#pragma once

#include <chrono>

namespace Engine
{
	/*!
	\class ChronoTimer
	Chrono timer class, creates a timer
	*/
	class ChronoTimer
	{
	public:
		inline void start() { m_startPoint = std::chrono::high_resolution_clock::now(); } //!< Starts the timer
		inline void reset() { m_startPoint = std::chrono::high_resolution_clock::now(); } //!< Resets the timer
		float getElapsedTime() //!< Getter for the elapsed time
		{
			m_endPoint = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float, std::milli> elapsed = m_endPoint - m_startPoint;
			return elapsed.count() / 1000.f;
		}

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_startPoint; //!< Starting point
		std::chrono::time_point<std::chrono::high_resolution_clock> m_endPoint; //!< Ending point
	};




}