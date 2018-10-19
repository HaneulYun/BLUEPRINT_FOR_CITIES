#include <gl/freeglut.h>
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
	camera.setPosition({ 0, 400, 400 });
	camera.setRotation({ -85, 90, 0 });

	camera.addChild(&plane);
	plane.setBeginMode(GL_QUADS);
	plane.vectors.push_back({ -300, 0,  300 });
	plane.vectors.push_back({ -300, 0, -300 });
	plane.vectors.push_back({  300, 0, -300 });
	plane.vectors.push_back({  300, 0,  300 });
	plane.setPosition({ 0.f, 0.f, 0.f });
	plane.setColor(0.5f, 0.5f, 0.5f);

}

void GameScene::update()
{
	camera.update();
}

void GameScene::render()
{
	camera.render();
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
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60, w / h, 1, 1000);
	glTranslatef(0.f, 0.f, 0.f);
}

void GameScene::keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'i':
		break;
	case 'w':	camera.adjustRotation(1, 0, 0);				break;
	case 's':	camera.adjustRotation(-1, 0, 0);			break;
	case 'a':	camera.adjustRotation(0, 1, 0);				break;
	case 'd':	camera.adjustRotation(0, -1, 0);			break;
	case 'q':	camera.adjustRotation(0, 0, -1);			break;
	case 'e':	camera.adjustRotation(0, 0, 1);				break;
	case '+':	camera.adjustPosition(0.f, 0.f, -10.f );	break;
	case '-':	camera.adjustPosition(0.f, 0.f, 10.f );		break;
	case 't':
	case 'g':
	case 'f':
	case 'h':
	case 'r':
	case 'y':
		break;
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
	default:
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
	switch (button)
	{
	}
}

void GameScene::timerFunction(int value)
{
	update();
	glutTimerFunc(1000 / 60, App::TimerFunction, 1);
	glutPostRedisplay();
}