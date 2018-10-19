#include "App.h"
#include "GameScene.h"

App* App::m_instance = nullptr;

App::App(int argc, char** argv) : m_argc(argc), m_argv(argv),
	m_winPosition({ NULL, NULL }), m_winSize({ NULL, NULL }),
	m_title(nullptr), m_pScene(nullptr)
{
}

App::~App()
{
	release();
}

App* App::create(int argc, char** argv)
{
	if (!m_instance)
		m_instance = new App(argc, argv);
	return m_instance;
}

App* App::instance()
{
	if (m_instance)
		return m_instance;
	return nullptr;
}

void App::initialize(POINT winPosition, SIZE winSize, char* title)
{
	m_winPosition = winPosition;
	m_winSize = winSize;

	m_title = new char[strlen(title) + 1];
	strcpy_s(m_title, strlen(title) + 1, title);

	GLinit();
}

void App::initialize(int x, int y, int width, int height, char* title)
{
	m_winPosition = { x , y };
	m_winSize = { width, height };

	m_title = new char[strlen(title) + 1];
	strcpy_s(m_title, strlen(title) + 1, title);

	GLinit();

	m_pScene = new GameScene();
	if (m_pScene)
		m_pScene->initialize();
}

void App::GLinit()
{
	glutInit(&m_argc, m_argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(m_winPosition.x, m_winPosition.y);
	glutInitWindowSize(m_winSize.cx, m_winSize.cy);
	glutCreateWindow(m_title);
	glEnable(GL_DEPTH_TEST);
}

void App::release()
{
	if (m_pScene)
	{
		m_pScene->release();
		delete m_pScene;
	}
	delete[] m_title;
}

int App::run()
{
	glutDisplayFunc(App::drawScene);
	glutReshapeFunc(App::Reshape);
	glutKeyboardFunc(App::Keyboard);
	glutSpecialFunc(App::Special);
	glutMouseFunc(App::Mouse);
	glutMotionFunc(App::Motion);
	glutCreateMenu(App::MenuFunc);
	glutTimerFunc(1000 / 60, App::TimerFunction, 1);
	glutMainLoop();
	return 0;
}

GLvoid App::drawScene(GLvoid)
{
	if (g_app->m_pScene)
		g_app->m_pScene->drawScene();
}

GLvoid App::Reshape(int w, int h)
{
	if (g_app->m_pScene)
		g_app->m_pScene->reshape(w, h);
}

GLvoid App::Keyboard(unsigned char key, int x, int y)
{
	if (g_app->m_pScene)
		g_app->m_pScene->keyboard(key, x, y);
}

GLvoid App::Special(int key, int x, int y)
{
	if (g_app->m_pScene)
		g_app->m_pScene->special(key, x, y);
}

GLvoid App::Mouse(int button, int state, int x, int y)
{
	if (g_app->m_pScene)
		g_app->m_pScene->mouse(button, state, x, y);
}

GLvoid App::Motion(int x, int y)
{
	if (g_app->m_pScene)
		g_app->m_pScene->motion(x, y);
}

GLvoid App::MenuFunc(int button)
{
	if (g_app->m_pScene)
		g_app->m_pScene->menuFunc(button);
}

GLvoid App::TimerFunction(int value)
{
	if (g_app->m_pScene)
		g_app->m_pScene->timerFunction(value);
}