#include "eventHandlerTests.h"
#include "GLFW/GLFWCodes.h"

TEST(EventHandler, onClose) {
	MockApplication app;

	Engine::WindowCloseEvent i;

	bool handledDefault = i.handled();
	app.runMock();
	bool handledBefore = i.handled();
	auto& onCloseFunction = app.m_handler.getOnCloseCallback();
	onCloseFunction(i);
	bool handledAfter = i.handled();

	EXPECT_EQ(handledDefault, false);
	EXPECT_EQ(handledDefault, handledBefore);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}

TEST(EventHandler, onMoved) {
	MockApplication app;

	Engine::WindowMoved i(2.f, 3.f);

	auto pos1 = i.getPos();
	bool handledDefault = i.handled();
	app.runMock();
	bool handledBefore = i.handled();
	auto& onMovedFunction = app.m_handler.getOnMoveFunction();
	onMovedFunction(i);
	bool handledAfter = i.handled();


	EXPECT_EQ(i.getX(), 2.f);
	EXPECT_EQ(i.getY(), 3.f);

	EXPECT_EQ(handledDefault, false);
	EXPECT_EQ(handledDefault, handledBefore);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}

TEST(EventHandler, onLostFocus) { // also a relevant test of lost focus functioning
	MockApplication app; 

	Engine::WindowLostFocus i;

	bool handledDefault = i.handled();
	app.runMock();
	bool handledBefore = i.handled();
	auto& onLostFocusFunction = app.m_handler.getOnFocusLost();
	onLostFocusFunction(i);
	bool handledAfter = i.handled();

	EXPECT_EQ(handledDefault, false);
	EXPECT_EQ(handledDefault, handledBefore);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}

TEST(EventHandler, onGainedFocus) { // also a relevant test of gained focus functioning
	MockApplication app;

	Engine::WindowFocus i;

	bool handledDefault = i.handled();
	app.runMock();
	bool handledBefore = i.handled();
	auto& onFocusFunction = app.m_handler.getOnFocused();
	onFocusFunction(i);
	bool handledAfter = i.handled();

	EXPECT_EQ(handledDefault, false);
	EXPECT_EQ(handledDefault, handledBefore);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}

TEST(EventHandler, onWindowResize) {
	MockApplication app;

	Engine::WindowResizeEvent i(2.f, 2.f);

	bool handledDefault = i.handled();
	app.runMock();
	bool handledBefore = i.handled();
	auto& onResizeFunction = app.m_handler.getOnResizeCallback();
	onResizeFunction(i);
	bool handledAfter = i.handled();

	EXPECT_EQ(i.getSize().x, 2.f);
	EXPECT_EQ(i.getSize().y, 2.f);

	EXPECT_EQ(handledDefault, false);
	EXPECT_EQ(handledDefault, handledBefore);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}

TEST(EventHandler, onKeyPressed) {
	MockApplication app;

	Engine::KeyPressed i(NG_KEY_A, 0);

	bool handledDefault = i.handled();
	app.runMock();
	bool handledBefore = i.handled();
	auto& onKeyPressedFunction = app.m_handler.getOnKeyPressed();
	onKeyPressedFunction(i);
	bool handledAfter = i.handled();

	EXPECT_EQ(NG_KEY_A, i.getKeyCode());

	EXPECT_EQ(handledDefault, false);
	EXPECT_EQ(handledDefault, handledBefore);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}

TEST(EventHandler, onKeyReleased) {
	MockApplication app;

	Engine::KeyReleased i(NG_KEY_A);

	bool handledDefault = i.handled();
	app.runMock();
	bool handledBefore = i.handled();
	auto& onKeyReleasedFunction = app.m_handler.getOnKeyReleased();
	onKeyReleasedFunction(i);
	bool handledAfter = i.handled();

	EXPECT_EQ(NG_KEY_A, i.getKeyCode());

	EXPECT_EQ(handledDefault, false);
	EXPECT_EQ(handledDefault, handledBefore);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}

TEST(EventHandler, onKeyTyped) {
	MockApplication app;

	Engine::KeyTyped i(NG_KEY_A);

	bool handledDefault = i.handled();
	app.runMock();
	bool handledBefore = i.handled();
	auto& onKeyTypedFunction = app.m_handler.getOnKeyTyped();
	onKeyTypedFunction(i);
	bool handledAfter = i.handled();

	EXPECT_EQ(NG_KEY_A, i.getKeyCode());

	EXPECT_EQ(handledDefault, false);
	EXPECT_EQ(handledDefault, handledBefore);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}

TEST(EventHandler, onMouseMoved) {
	MockApplication app;

	Engine::MouseMoved i(0.f, 0.f);

	bool handledDefault = i.handled();
	app.runMock();
	bool handledBefore = i.handled();
	auto& onMouseMovedFunction = app.m_handler.getOnMouseMoved();
	onMouseMovedFunction(i);
	bool handledAfter = i.handled();

	EXPECT_EQ(glm::vec2(0.f, 0.f), i.getPos());

	EXPECT_EQ(handledDefault, false);
	EXPECT_EQ(handledDefault, handledBefore);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}

TEST(EventHandler, onMousePressed) {
	MockApplication app;

	Engine::MouseButtonPressed i(1);

	bool handledDefault = i.handled();
	app.runMock();
	bool handledBefore = i.handled();
	auto& onMousePressFunction = app.m_handler.getOnMousePressed();
	onMousePressFunction(i);
	bool handledAfter = i.handled();

	EXPECT_EQ(1, i.getMouseButton());

	EXPECT_EQ(handledDefault, false);
	EXPECT_EQ(handledDefault, handledBefore);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}

TEST(EventHandler, onMouseReleased) {
	MockApplication app;

	Engine::MouseButtonReleased i(1);

	bool handledDefault = i.handled();
	app.runMock();
	bool handledBefore = i.handled();
	auto& onMouseReleasedFunction = app.m_handler.getOnMouseReleased();
	onMouseReleasedFunction(i);
	bool handledAfter = i.handled();

	EXPECT_EQ(1, i.getMouseButton());

	EXPECT_EQ(handledDefault, false);
	EXPECT_EQ(handledDefault, handledBefore);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}

TEST(EventHandler, onMouseScrolled) {
	MockApplication app;

	Engine::MouseScrolled i(0.f, 0.f);

	bool handledDefault = i.handled();
	app.runMock();
	bool handledBefore = i.handled();
	auto& onMouseScrollFunction = app.m_handler.getOnMouseScrolled();
	onMouseScrollFunction(i);
	bool handledAfter = i.handled();

	EXPECT_EQ(handledDefault, false);
	EXPECT_EQ(handledDefault, handledBefore);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}
