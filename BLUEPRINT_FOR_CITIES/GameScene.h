#pragma once
#include "Scene.h"
#include "Object3d.h"
#include "Tree.h"
#include "Terrain.h"
#include "TopBar.h"
#include "LowerBar.h"
#include "CarAmbo.h"
#include "Cloud.h"
#include "TimeBar.h"

class GameScene : public Scene
{
	static GameScene* m_instance;

	Tree tree[100];
	TopBar topBar;
	LowerBar lowerBar;
	CarAmbo carAmbo[20];
	Cloud cloud[10];
	TimeBar timeBar;

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