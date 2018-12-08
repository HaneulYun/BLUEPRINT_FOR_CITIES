#pragma once
#include "Scene.h"
#include "Object3d.h"
#include "Terrain.h"
#include "picking.h"

#include "Tree.h"
#include "TopBar.h"
#include "LowerBar.h"
#include "CarAmbo.h"
#include "Cloud.h"
#include "TimeBar.h"
#include "StreetLight.h"
#include "DestroyEffect.h"

class GameScene : public Scene
{
	static GameScene* m_instance;

	TopBar topBar;
	LowerBar lowerBar;
	CarAmbo carAmbo[20];
	Cloud cloud[10];
	TimeBar timeBar;
	DestroyEffect destroyEffect;
	StreetLight streetLight[50];

public:
	Tree treeOnMouse;
	std::list<Tree*> tree;
	Terrain* terrain;
	MousePicker* mousePicker;

public:
	bool viewMode{ true };
	bool destroyMode{ false };

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