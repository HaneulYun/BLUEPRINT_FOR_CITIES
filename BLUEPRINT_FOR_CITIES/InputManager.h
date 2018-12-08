#pragma once

#define g_pInputManager	InputManager::instance()

#define g_pKeyCodeScan(vk) ((g_pInputManager->m_OldKeyState[vk])&&(g_pInputManager->m_CurKeyState[vk]))

class InputManager
{
public:
	bool oldKeyState[348];
	bool curKeyState[348];
	bool oldMouseState[2];
	bool curMouseState[2];
	double xpos;
	double ypos;
	static InputManager* m_instance;

public:
	InputManager();
	~InputManager();

	static InputManager* create();
	static InputManager* instance();

	void initialize();
	void update();
};