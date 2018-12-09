#include <random>
#include <chrono>

#include "GameScene.h"
#include "controls.hpp"
#include "InputManager.h"

#define PI 3.141592

GameScene* GameScene::m_instance = nullptr;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

GameScene* GameScene::create()
{
	if (!m_instance)
		m_instance = new GameScene();
	return m_instance;
}

GameScene* GameScene::instance()
{
	if (m_instance)
		return m_instance;
	return nullptr;
}

void GameScene::initialize()
{
	terrain = new Terrain();
	terrain->setTerrainSize(20, 20);
	terrain->loadTerrain("resources\\map.bmp", 5);

	mousePicker = new MousePicker(getProjectionMatrix(), terrain);

	selectProp.initialize();
	selectRoad.initialize();
	selectGrid.initialize();
	pathManager.initialize();
	propManager.initialize();
	for (auto& v : carAmbo)
		v.initialize();
	sun.initialize();
	topBar.initialize();
	lowerBar.initialize();
	timeBar.initialize();
	destroyEffect.initialize();
	fasterImage.initialize();
	pauseImage.initialize();

	texture.initialize();
}

void GameScene::update()
{
	computeMatricesFromInputs();
	if (!viewMode)
	{
		mousePicker->update();
		glm::vec3 v = mousePicker->currentTerrainPoint;
		if (v != glm::vec3{})
		{
			v.y = g_gameScene->terrain->getHeightByPosition(v.x, v.z);
		}
	}
	terrain->update();
	sun.update();

	selectProp.update();
	selectRoad.update();
	selectGrid.update();
	pathManager.update();
	propManager.update();
	for (auto& v : carAmbo)
		v.update();
	topBar.update();
	lowerBar.update();
	timeBar.update();
	destroyEffect.update();
	fasterImage.update();
	pauseImage.update();
}

void GameScene::render()
{
	texture.bindTexture();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	pathManager.extractDepthmap();
	propManager.extractDepthmap();
	terrain->extractDepthmap();

	texture.freeTexture();
	sun.render();

	selectProp.render();
	selectRoad.render();
	selectGrid.render();
	pathManager.render();
	propManager.render();
	terrain->render();
	for (auto& v : carAmbo)
		v.render();
	topBar.render();
	lowerBar.render();
	timeBar.render();
	destroyEffect.render();
	fasterImage.render();
	pauseImage.render();

	glViewport(0, 0, 1600, 900);
	//texture.render();
}

void GameScene::release()
{
	terrain->release();
	sun.release();

	selectProp.release();
	selectRoad.release();
	selectGrid.release();
	pathManager.release();
	propManager.release();
	for (auto& v : carAmbo)
		v.release();
	topBar.release();
	lowerBar.release();
	timeBar.release();
	destroyEffect.release();
	fasterImage.release();
	pauseImage.release();
}