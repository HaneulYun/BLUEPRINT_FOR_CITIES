#pragma once
#include "Scene.h"
#include "Object3d.h"

class GameScene : public Scene
{
	Object3d obj[10][10];
public:
	GameScene();
	~GameScene();

	void initialize();
	void update();
	void render();
	void release();
};