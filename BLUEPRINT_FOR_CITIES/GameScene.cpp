#include <gl/glew.h>
#include <gl/gl.h>
#include "GameScene.h"
#include "App.h"

#define PI 3.141592f

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::initialize()
{
	camera.setPosition({ 0, 300, 300 });
	camera.setRotation({ -45, 90, 0 });

	// plane
	{
		camera.addChild(&plane);
		plane.setBeginMode(GL_QUADS);
		plane.vectors.push_back({ -200, 0, -200 });
		plane.vectors.push_back({ -200, 0,  200 });
		plane.vectors.push_back({  200, 0,  200 });
		plane.vectors.push_back({  200, 0, -200 });
		plane.setPosition({ 0.f, 0.f, 0.f });
		plane.setColor(0.5f, 0.5f, 0.5f);
	}

	camera.addChild(&obj);
	obj.loadOBJ("resources/chicken.obj");
}

void GameScene::update()
{
	camera.update();
}

void GameScene::render()
{
	camera.render();
	//static const GLfloat g_vertex_buffer_data[] =
	//{
	//	-100.f, -100.f, 0.f,
	//	100.f, -100.f, 0.f,
	//	0.f, 100.f, 0.f
	//};
	//
	//GLuint vertexbuffer;
	//glGenBuffers(1, &vertexbuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW)
}

void GameScene::release()
{
}

void GameScene::drawScene(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	render();

	glutSwapBuffers();
}

void GameScene::reshape(int w, int h)
{
	viewportWidth = w;
	viewportHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60, w / h, 1, 1000);
	//glOrtho(-400, 400, -300, 300, -1000, 1000);

	glTranslatef(0.f, 0.f, 0.f);
}

void GameScene::keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '0':
		camera.setRotation(0, 0, 0);
		camera.setPosition(0, 0, 0);
		break;
	case 'w':	camera.adjustRotation(1, 0, 0);			break;
	case 's':	camera.adjustRotation(-1, 0, 0);		break;
	case 'a':	camera.adjustRotation(0, 1, 0);			break;
	case 'd':	camera.adjustRotation(0, -1, 0);		break;
	case 'q':	camera.adjustRotation(0, 0, -1);		break;
	case 'e':	camera.adjustRotation(0, 0, 1);			break;
	case '+':	camera.adjustPosition(0.f, 0.f, -10.f);	break;
	case '-':	camera.adjustPosition(0.f, 0.f, 10.f);	break;
	}
}

void GameScene::special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		camera.adjustPosition({ -10.f, 0.f, 0.f });
		break;
	case GLUT_KEY_RIGHT:
		camera.adjustPosition({ 10.f, 0.f, 0.f });
		break;
	case GLUT_KEY_UP:
		camera.adjustPosition({ 0.f, 10.f, 0.f });
		break;
	case GLUT_KEY_DOWN:
		camera.adjustPosition({ 0.f, -10.f, 0.f });
		break;
	}
}

void GameScene::mouse(int button, int state, int x, int y)
{
}

void GameScene::motion(int x, int y)
{
}

void GameScene::menuFunc(int button)
{
}

void GameScene::timerFunction(int value)
{
	update();
	glutTimerFunc(1000 / 60, App::TimerFunction, 1);
	glutPostRedisplay();
}