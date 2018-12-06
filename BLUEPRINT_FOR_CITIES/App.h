#pragma once
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <Windows.h>
#include "Scene.h"
#include "InputManager.h"

#pragma comment (lib, "opengl32.lib")

class App
{
	static App* m_instance;
	GLFWwindow* window{ nullptr };
	GLuint	VertexArrayID{ NULL };

	POINT	m_winPosition{ NULL, NULL };
	SIZE	m_winSize{ NULL,NULL };
	char*	m_title{ nullptr };
	
	Scene*	m_pScene{ nullptr };

	InputManager* m_pInputManager{ nullptr };

	App();
	~App();

public:

public:
	static App* create();
	static App* instance();

	void initialize(int x, int y, int width, int height, char* title);
	void update();
	void render();
	void release();

	int GLFWinit();
	int run();

	Scene* getScene();
	SIZE getSize() const { return m_winSize; }

};

#define g_app App::instance()
#define g_scene g_app->getScene()