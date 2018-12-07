#pragma once
#include "Scene.h"
#include "Object3d.h"
#include "Tree.h"
#include "Terrain.h"

class GameScene : public Scene
{
	static GameScene* m_instance;

	Tree tree[100];

public:
	Terrain terrain;

public:
	bool viewMode{ true };

private:
	GameScene();
	~GameScene();

public:
	static GameScene* create();
	static GameScene* instance();

	void initialize();
	void update();
	void render();
	void release();
};

#define g_gameScene GameScene::instance()