#pragma once
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <gl/freeglut.h>
#include "Scene.h"

class App
{
	static App* m_instance;

	int		m_argc;
	char**	m_argv;
	POINT	m_winPosition;
	char*	m_title;
	
	App();
	~App();

	GLFWwindow* window;

	Scene*	m_pScene;

public:
	SIZE	m_winSize;

public:
	static App* create();
	static App* instance();

	void initialize(POINT winPosition, SIZE winSize, char* title);
	void initialize(int x, int y, int width, int height, char* title);
	int GLFWinit();
	void release();

	Scene* getScene();

	int run();
};

#define g_app App::instance()
#define g_scene g_app->getScene()