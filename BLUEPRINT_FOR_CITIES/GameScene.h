#pragma once
#include "Scene.h"
#include "Object3d.h"
#include "Tree.h"

class GameScene : public Scene
{
	Tree tree[100];
public:
	GameScene();
	~GameScene();

	void initialize();
	void update();
	void render();
	void release();
};