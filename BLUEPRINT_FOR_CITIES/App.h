#pragma once
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <Windows.h>
#include "Scene.h"

#pragma comment (lib, "opengl32.lib")

class App
{
	static App* m_instance;
	GLFWwindow* window{ nullptr };

	POINT	m_winPosition{ NULL, NULL };
	SIZE	m_winSize{ NULL,NULL };
	char*	m_title{ nullptr };
	
	Scene*	m_pScene{ nullptr };

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

};

#define g_app App::instance()
#define g_scene g_app->getScene()