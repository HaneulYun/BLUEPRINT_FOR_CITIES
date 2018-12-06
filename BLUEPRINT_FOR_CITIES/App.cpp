#include "App.h"
#include "GameScene.h"

App* App::m_instance = nullptr;
extern GLFWwindow* window;

App::App()
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

void App::initialize(int x, int y, int width, int height, char* title)
{
	m_winPosition = { x , y };
	m_winSize = { width, height };

	m_title = new char[strlen(title) + 1];
	strcpy_s(m_title, strlen(title) + 1, title);

	GLFWinit();

	m_pScene = GameScene::create();
	if (m_pScene)
		m_pScene->initialize();

	m_pInputManager = InputManager::create();
	if (m_pInputManager)
		m_pInputManager->initialize();
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

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glDepthFunc(GL_LESS);
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glfwPollEvents();
	glfwSetCursorPos(window, m_winSize.cx / 2, m_winSize.cy / 2);

}

void App::update()
{
	m_pScene->update();
}

void App::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_pScene->render();
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void App::release()
{
	if (m_pScene)
	{
		m_pScene->release();
		delete m_pScene;
	}
	delete[] m_title;

	glDeleteVertexArrays(1, &VertexArrayID);
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}

int App::run()
{
	do {
		update();
		render();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
	return 0;
}

Scene* App::getScene()
{
	return m_pScene;
}