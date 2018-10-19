#pragma once
#include <gl/freeglut.h>
#include "Scene.h"

class App
{
	static App* m_instance;

	int		m_argc;
	char**	m_argv;
	POINT	m_winPosition;
	char*	m_title;
	
	App(int argc, char** argv);
	~App();

	Scene*	m_pScene;

public:
	SIZE	m_winSize;

public:
	static App* create(int argc, char** argv);
	static App* instance();

	void initialize(POINT winPosition, SIZE winSize, char* title);
	void initialize(int x, int y, int width, int height, char* title);
	void GLinit();
	void release();

	static GLvoid drawScene(GLvoid);
	static GLvoid Reshape(int w, int h);
	static GLvoid Keyboard(unsigned char key, int x, int y);
	static GLvoid Special(int key, int x, int y);
	static GLvoid Mouse(int button, int state, int x, int y);
	static GLvoid Motion(int x, int y);
	static GLvoid MenuFunc(int button);
	static GLvoid TimerFunction(int value);

	int run();
};

#define g_app App::instance()