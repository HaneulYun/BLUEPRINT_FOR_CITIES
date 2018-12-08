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

	pathManager.initialize();
	propManager.initialize();
	for (auto& v : carAmbo)
		v.initialize();
	sun.initialize();
	burgerOnMouse.initialize();
	topBar.initialize();
	lowerBar.initialize();
	timeBar.initialize();
	destroyEffect.initialize();
	fasterImage.initialize();
	pauseImage.initialize();
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
			if (pathManager.drawState)
				burgerOnMouse.obj.setPosition(v);
		}
	}
	
	terrain->update();
	sun.update();
	pathManager.update();
	propManager.update();
	for (auto& v : carAmbo)
		v.update();
	burgerOnMouse.update();
	topBar.update();
	lowerBar.update();
	timeBar.update();
	destroyEffect.update();
	fasterImage.update();
	pauseImage.update();
}

void GameScene::render()
{
	terrain->render();
	sun.render();
	pathManager.render();
	propManager.render();
	for (auto& v : carAmbo)
	topBar.render();
	lowerBar.render();
	timeBar.render();
	destroyEffect.render();
	fasterImage.render();
	pauseImage.render();
	if (!viewMode)
	{
		if (pathManager.drawState)
			burgerOnMouse.render();
	}
}

void GameScene::release()
{
	terrain->release();
	sun.release();
	pathManager.release();
	propManager.release();
	for (auto& v : carAmbo)
		v.release();
	burgerOnMouse.release();
	topBar.release();
	lowerBar.release();
	timeBar.release();
	destroyEffect.release();
	fasterImage.release();
	pauseImage.release();
}