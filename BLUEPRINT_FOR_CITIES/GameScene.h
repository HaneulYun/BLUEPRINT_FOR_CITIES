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
#include "Pause.h"

#include "PathManager.h"
#include "PropManager.h"
#include "TextureFromRender.h"
#include "SelectProp.h"
#include "SelectRoad.h"
#include "SelectGrid.h"

class GameScene : public Scene
{
	static GameScene* m_instance;

	TimeBar timeBar;
	DestroyEffect destroyEffect;

	CarAmbo carAmbo[20];

public:
	TopBar topBar;
	LowerBar lowerBar;
	SelectProp selectProp;
	SelectRoad selectRoad;
	SelectGrid selectGrid;
	TextureFromRender texture;
	PathManager pathManager;
	PropManager propManager;
	Faster fasterImage;
	Pause pauseImage;
	Sun sun;
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