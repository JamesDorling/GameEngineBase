/*! \file log.cpp */
#include "engine_pch.h"
#include "systems/log.h"


namespace Engine {

	std::shared_ptr<spdlog::logger> Log::s_consoleLogger = nullptr; //!< Initialise the console logger
	std::shared_ptr<spdlog::logger> Log::s_fileLogger = nullptr; //!< Initialise the file logger

	void Log::start(SystemSignal init, ...)
	{
	spdlog::set_pattern("%^[%T]: %v%$"); //!< Set the logger's pattern 
	spdlog::set_level(spdlog::level::trace); //!< Set tje logger's level

	s_consoleLogger = spdlog::stdout_color_mt("Console"); //!< Assign the logger's colour

	char filepath[256] = "logs/"; //!< Set the filepath for the file logger
	char time[128]; //!< Time, used at the start of the file logger's logs
	/*
	std::time_t t = std::time(nullptr);
	std::strftime(time, sizeof(time), "%d_%m_%y %I_%M_%S", std::localtime(&t));
	strcat_s(filepath, time);
	strcat_s(filepath, ".txt");

	s_fileLogger = spdlog::basic_logger_mt("File", filepath);
	*/
	}

	void Log::stop(SystemSignal close, ...)
	{
		s_consoleLogger->info("Stopping console logger"); //!< Log the console logger's stop call
		s_consoleLogger.reset(); //!< Reset the logger's pointer
	}
}