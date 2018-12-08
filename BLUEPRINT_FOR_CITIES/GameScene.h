#pragma once
#include "Scene.h"
#include "Object3d.h"
#include "Terrain.h"
#include "picking.h"

#include "TopBar.h"
#include "LowerBar.h"
#include "CarAmbo.h"
#include "TimeBar.h"
#include "DestroyEffect.h"
#include "Sun.h"
#include "Faster.h"

#include "PathManager.h"
#include "PropManager.h"

class GameScene : public Scene
{
	static GameScene* m_instance;

	TopBar topBar;
	LowerBar lowerBar;
	TimeBar timeBar;
	DestroyEffect destroyEffect;

	CarAmbo carAmbo[20];

public:
	PathManager pathManager;
	PropManager propManager;
	Faster fasterImage;
	Sun sun;
	Node burgerOnMouse;
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