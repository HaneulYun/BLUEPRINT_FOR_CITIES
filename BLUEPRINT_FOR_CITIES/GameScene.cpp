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
	terrain->extractDepthmap();
	for (auto& v : tree)
		v->extractDepthmap();
	for (auto& v : carAmbo)
		v.extractDepthmap();
	for (auto& v : cloud)
		v.extractDepthmap();
	for (auto& v : streetLight)
		v.extractDepthmap();

	texture.freeTexture();
	sun.render();
	pathManager.render();
	propManager.render();
	terrain->render();
	for (auto& v : tree)
		v->render();
	for (auto& v : carAmbo)
	topBar.render();
	lowerBar.render();
	timeBar.render();
	destroyEffect.render();
	fasterImage.render();
	pauseImage.render();
	if (!viewMode)
	{
		if (!pathManager.drawState)
			treeOnMouse.render();
		else
		{
			burgerOnMouse.render();
		}
	}

	glViewport(0, 0, 1600, 900);
	//texture.render();
}

void GameScene::release()
{
	terrain->release();
	sun.release();
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