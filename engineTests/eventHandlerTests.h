#pragma once

#include <gtest/gtest.h>
#include "events/eventHandler.h"

class MockApplication
{
public:
	Engine::EventHandler m_handler;
	void runMock()
	{
		//Window Events
		m_handler.setOnCloseCallback(std::bind(&MockApplication::onClose, this, std::placeholders::_1));
		m_handler.setOnMovedWinCallback(std::bind(&MockApplication::onMoved, this, std::placeholders::_1));
		m_handler.setOnFocusCallback(std::bind(&MockApplication::onGainedFocus, this, std::placeholders::_1));
		m_handler.setOnLostFocusCallback(std::bind(&MockApplication::onLostFocus, this, std::placeholders::_1));
		m_handler.setOnResizeCallback(std::bind(&MockApplication::onResize, this, std::placeholders::_1));
		// Key events
		m_handler.setOnKeyPressedCallback(std::bind(&MockApplication::onKeyPress, this, std::placeholders::_1));
		m_handler.setOnKeyReleasedCallback(std::bind(&MockApplication::onKeyReleased, this, std::placeholders::_1));
		m_handler.setOnKeyTypedCallback(std::bind(&MockApplication::onKeyTyped, this, std::placeholders::_1));
		// Mouse events
		m_handler.setOnMouseMovedCallback(std::bind(&MockApplication::onMouseMoved, this, std::placeholders::_1));
		m_handler.setOnMousePressedCallback(std::bind(&MockApplication::onMousePressed, this, std::placeholders::_1));
		m_handler.setOnMouseReleasedCallback(std::bind(&MockApplication::onMouseReleased, this, std::placeholders::_1));
		m_handler.setOnMouseScrolledCallback(std::bind(&MockApplication::onMouseScrolled, this, std::placeholders::_1));
	}
private:
	bool onClose(Engine::WindowCloseEvent& i) 
	{
		i.handle(true);
		return i.handled();
	}
	bool onMoved(Engine::WindowMoved& i)
	{
		i.handle(true);
		return i.handled();
	}
	bool onGainedFocus(Engine::WindowFocus& i)
	{
		i.handle(true);
		return i.handled();
	}
	bool onLostFocus(Engine::WindowLostFocus& i)
	{
		i.handle(true);
		return i.handled();
	}
	bool onResize(Engine::WindowResizeEvent& i)
	{
		i.handle(true);
		return i.handled();
	}
	bool onKeyPress(Engine::KeyPressed& i)
	{
		i.handle(true);
		return i.handled();
	}
	bool onKeyReleased(Engine::KeyReleased& i)
	{
		i.handle(true);
		return i.handled();
	}
	bool onKeyTyped(Engine::KeyTyped& i)
	{
		i.handle(true);
		return i.handled();
	}
	bool onMouseMoved(Engine::MouseMoved& i)
	{
		i.handle(true);
		return i.handled();
	}
	bool onMousePressed(Engine::MouseButtonPressed& i)
	{
		i.handle(true);
		return i.handled();
	}
	bool onMouseReleased(Engine::MouseButtonReleased& i)
	{
		i.handle(true);
		return i.handled();
	}
	bool onMouseScrolled(Engine::MouseScrolled& i)
	{
		i.handle(true);
		return i.handled();
	}
};