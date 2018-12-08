// Include GLFW
#include <gl/glew.h>
#include <GLFW/glfw3.h>
extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

#include <iostream>
#include "InputManager.h"

InputManager* InputManager::m_instance = nullptr;

InputManager::InputManager()
{
	if (m_instance == nullptr)
		m_instance = this;
	initialize();
}

InputManager::~InputManager()
{
}

InputManager* InputManager::create()
{
	if (!m_instance)
		m_instance = new InputManager();
	return m_instance;
}

InputManager* InputManager::instance()
{
	if (m_instance)
		return m_instance;
	return nullptr;
}

void InputManager::initialize()
{
	for (int i = 0; i < 348; ++i)
	{
		oldKeyState[i] = false;
		curKeyState[i] = false;
	}
	for (int i = 0; i < 2; ++i)
	{
		oldMouseState[i] = false;
		curMouseState[i] = false;
	}
	glfwGetCursorPos(window, &xpos, &ypos);
}

void InputManager::update()
{
	memcpy(oldKeyState, curKeyState, 348);
	memcpy(oldMouseState, curMouseState, 2);
	glfwGetCursorPos(window, &xpos, &ypos);
}