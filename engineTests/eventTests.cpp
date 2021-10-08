#include "eventTests.h"

TEST(Events, ResizeConstructor) {
	Engine::WindowResizeEvent size1(800, 600);
	int32_t width_1 = size1.getWidth();
	int32_t height_1 = size1.getHeight();

	auto size2 = size1.getSize();
	int32_t width_2 = size2.x;
	int32_t height_2 = size2.y;

	int32_t cat = size1.getCategoryFlag();
	Engine::EventType type = size1.getEventType();
	Engine::EventType staticType = size1.getStaticType();

	EXPECT_EQ(width_1, 800);
	EXPECT_EQ(width_2, 800);
	EXPECT_EQ(height_1, 600);
	EXPECT_EQ(height_2, 600);
	EXPECT_EQ(cat, Engine::EventCategory::EventCategoryWindow);
	EXPECT_TRUE(size1.isInCategory(Engine::EventCategoryWindow));
	EXPECT_EQ(type, staticType);
	EXPECT_EQ(type, Engine::EventType::WindowResize);
}

TEST(Events, moveConstructor) {
	Engine::WindowMoved pos1(2.f, 3.f);
	int32_t xPos1 = pos1.getX();
	int32_t yPos1 = pos1.getY();

	auto pos2 = pos1.getPos();
	int32_t xPos2 = pos2.x;
	int32_t yPos2 = pos2.y;

	int32_t cat = pos1.getCategoryFlag();
	Engine::EventType type = pos1.getEventType();
	Engine::EventType staticType = pos1.getStaticType();

	EXPECT_EQ(xPos1, 2.f);
	EXPECT_EQ(xPos2, 2.f);
	EXPECT_EQ(yPos1, 3.f);
	EXPECT_EQ(yPos2, 3.f);
	EXPECT_EQ(cat, Engine::EventCategory::EventCategoryWindow);
	EXPECT_TRUE(pos1.isInCategory(Engine::EventCategoryWindow));
	EXPECT_EQ(type, staticType);
	EXPECT_EQ(type, Engine::EventType::WindowMoved);
}

TEST(Events, closeEvent) {
	Engine::WindowCloseEvent i;

	int32_t cat = i.getCategoryFlag();
	Engine::EventType type = i.getEventType();
	Engine::EventType staticType = i.getStaticType();

	EXPECT_EQ(cat, Engine::EventCategory::EventCategoryWindow);
	EXPECT_TRUE(i.isInCategory(Engine::EventCategoryWindow));
	EXPECT_EQ(type, staticType);
	EXPECT_EQ(type, Engine::EventType::WindowClose);
}

TEST(Events, FocusGainEvent) {
	Engine::WindowFocus i;

	int32_t cat = i.getCategoryFlag();
	Engine::EventType type = i.getEventType();
	Engine::EventType staticType = i.getStaticType();

	EXPECT_EQ(cat, Engine::EventCategory::EventCategoryWindow);
	EXPECT_TRUE(i.isInCategory(Engine::EventCategoryWindow));
	EXPECT_EQ(type, staticType);
	EXPECT_EQ(type, Engine::EventType::WindowFocus);
}

TEST(Events, FocusLoseEvent) {
	Engine::WindowLostFocus i;

	int32_t cat = i.getCategoryFlag();
	Engine::EventType type = i.getEventType();
	Engine::EventType staticType = i.getStaticType();

	EXPECT_EQ(cat, Engine::EventCategory::EventCategoryWindow);
	EXPECT_TRUE(i.isInCategory(Engine::EventCategoryWindow));
	EXPECT_EQ(type, staticType);
	EXPECT_EQ(type, Engine::EventType::WindowLostFocus);
}

TEST(Events, KeyPressEvent) {
	Engine::KeyPressed key(1, 0);
	int32_t key1 = key.getKeyCode();
	int32_t repeat1 = key.getRepeatCount();

	int32_t cat = key.getCategoryFlag();
	Engine::EventType type = key.getEventType();
	Engine::EventType staticType = key.getStaticType();


	EXPECT_EQ(key1, 1);
	EXPECT_EQ(repeat1, 0);
	EXPECT_EQ(cat, Engine::EventCategory::EventCategoryKeyboard + Engine::EventCategory::EventCategoryInput);
	EXPECT_TRUE(key.isInCategory(Engine::EventCategoryKeyboard));
	EXPECT_EQ(type, staticType);
	EXPECT_EQ(type, Engine::EventType::KeyPressed);
}

TEST(Events, KeyReleasedEvent) {
	Engine::KeyReleased key(1);
	int32_t key1 = key.getKeyCode();

	int32_t cat = key.getCategoryFlag();
	Engine::EventType type = key.getEventType();
	Engine::EventType staticType = key.getStaticType();


	EXPECT_EQ(key1, 1);
	EXPECT_EQ(cat, Engine::EventCategory::EventCategoryKeyboard + Engine::EventCategory::EventCategoryInput);
	EXPECT_TRUE(key.isInCategory(Engine::EventCategoryKeyboard));
	EXPECT_EQ(type, staticType);
	EXPECT_EQ(type, Engine::EventType::KeyReleased);
}

TEST(Events, KeyTypedEvent) {
	Engine::KeyTyped key(1);
	int32_t key1 = key.getKeyCode();

	int32_t cat = key.getCategoryFlag();
	Engine::EventType type = key.getEventType();
	Engine::EventType staticType = key.getStaticType();


	EXPECT_EQ(key1, 1);
	EXPECT_EQ(cat, Engine::EventCategory::EventCategoryKeyboard + Engine::EventCategory::EventCategoryInput);
	EXPECT_TRUE(key.isInCategory(Engine::EventCategoryKeyboard));
	EXPECT_EQ(type, staticType);
	EXPECT_EQ(type, Engine::EventType::KeyTyped);
}

TEST(Events, mousePressEvent) {
	Engine::MouseButtonPressed button(1);
	int32_t button1 = button.getMouseButton();

	int32_t cat = button.getCategoryFlag();
	Engine::EventType type = button.getEventType();
	Engine::EventType staticType = button.getStaticType();


	EXPECT_EQ(button1, 1);
	EXPECT_EQ(cat, Engine::EventCategory::EventCategoryMouse + Engine::EventCategory::EventCategoryInput);
	EXPECT_TRUE(button.isInCategory(Engine::EventCategoryMouse));
	EXPECT_EQ(type, staticType);
	EXPECT_EQ(type, Engine::EventType::MouseButtonPressed);
}

TEST(Events, mouseReleasedEvent) {
	Engine::MouseButtonReleased button(1);
	int32_t button1 = button.getMouseButton();

	int32_t cat = button.getCategoryFlag();
	Engine::EventType type = button.getEventType();
	Engine::EventType staticType = button.getStaticType();


	EXPECT_EQ(button1, 1);
	EXPECT_EQ(cat, Engine::EventCategory::EventCategoryMouse + Engine::EventCategory::EventCategoryInput);
	EXPECT_TRUE(button.isInCategory(Engine::EventCategoryMouse));
	EXPECT_EQ(type, staticType);
	EXPECT_EQ(type, Engine::EventType::MouseButtonReleased);
}

TEST(Events, mouseMovedEvent) {
	Engine::MouseMoved i(2.f, 3.f);
	float x = i.getX();
	float y = i.getY();

	int32_t cat = i.getCategoryFlag();
	Engine::EventType type = i.getEventType();
	Engine::EventType staticType = i.getStaticType();


	EXPECT_EQ(x, 2.f);
	EXPECT_EQ(y, 3.f);
	EXPECT_EQ(cat, Engine::EventCategory::EventCategoryMouse + Engine::EventCategory::EventCategoryInput);
	EXPECT_TRUE(i.isInCategory(Engine::EventCategoryMouse));
	EXPECT_EQ(type, staticType);
	EXPECT_EQ(type, Engine::EventType::MouseMoved);
}

TEST(Events, mouseScrolledEvent) {
	Engine::MouseScrolled i(2.0, 3.0);

	int32_t x = i.getX();
	int32_t y = i.getY();

	int32_t cat = i.getCategoryFlag();
	Engine::EventType type = i.getEventType();
	Engine::EventType staticType = i.getStaticType();


	EXPECT_EQ(x, 2.0);
	EXPECT_EQ(y, 3.0);
	EXPECT_EQ(cat, Engine::EventCategory::EventCategoryMouse + Engine::EventCategory::EventCategoryInput);
	EXPECT_TRUE(i.isInCategory(Engine::EventCategoryMouse));
	EXPECT_EQ(type, staticType);
	EXPECT_EQ(type, Engine::EventType::MouseScrolled);
}
