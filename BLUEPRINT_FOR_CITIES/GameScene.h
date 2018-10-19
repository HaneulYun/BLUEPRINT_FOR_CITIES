#pragma once
#include <ctime>
#include <chrono>
#include "Scene.h"
#include "Object3d.h"
#include "ObjectGlutModel.h"
#include "ObjectFromObj.h"
#include "ObjectCamera.h"

class GameScene : public Scene
{
	ObjectCamera camera;
	Object3d plane;

public:
	GameScene();
	~GameScene();

	void initialize();
	void update();
	void render();
	void release();

	void drawScene(void);
	void reshape(int w, int h);
	void keyboard(unsigned char key, int x, int y);
	void special(int key, int x, int y);
	void mouse(int button, int state, int x, int y);
	void motion(int x, int y);
	void menuFunc(int button);
	void timerFunction(int value);
};