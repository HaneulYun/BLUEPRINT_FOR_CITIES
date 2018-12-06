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
		m_OldKeyState[i] = false;
		m_CurKeyState[i] = false;
	}
}

void InputManager::update()
{
	memcpy(m_OldKeyState, m_CurKeyState, 348);
}