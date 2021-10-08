/*! \file entryPoint.h
*/
#pragma once

#include "core/application.h"

extern Engine::Application* Engine::startApplication();

int main(int argc, char** argv)
{
	auto application = Engine::startApplication(); //!< Start the application
	application->run(); //!< Run the application
	delete application; //!< Delete the "auto application"

	return 0;
}

