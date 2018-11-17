#include "App.h"
#include "GameScene.h"

App* App::m_instance = nullptr;
extern GLFWwindow* window;

App::App() : m_argc(NULL), m_argv(nullptr),
	m_winPosition({ NULL, NULL }), m_winSize({ NULL, NULL }),
	m_title(nullptr), m_pScene(nullptr)
{
}

App::~App()
{
	release();
}

App* App::create()
{
	if (!m_instance)
		m_instance = new App();
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
	initialize(winPosition.x, winPosition.y, winSize.cx, winSize.cy, title);
}

void App::initialize(int x, int y, int width, int height, char* title)
{
	m_winPosition = { x , y };
	m_winSize = { width, height };

	m_title = new char[strlen(title) + 1];
	strcpy_s(m_title, strlen(title) + 1, title);

	//GLUTinit();
	GLFWinit();

	m_pScene = new GameScene();
	if (m_pScene)
		m_pScene->initialize();
}

int App::GLFWinit()
{
	if (!glfwInit())
	{
		fprintf(stderr, "GLFWinit failed\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	::window = window = glfwCreateWindow(m_winSize.cx, m_winSize.cy, m_title, NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "GLFWinit failed\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "GLEW failed\n");
		return -1;
	}

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glfwPollEvents();
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
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
	do {
		m_pScene->update();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_pScene->render();
		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
	return 0;
}

Scene* App::getScene()
{
	return m_pScene;
}