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

	sun.initialize();
	pathManager.initialize();
	tree.resize(100);
	for (auto& v : tree)
	{
		v = new Tree();
		v->initialize();
	}
	for (auto& v : carAmbo)
		v.initialize();
	for (auto& v : cloud)
		v.initialize();
	for (auto& v : streetLight)
		v.initialize();
	treeOnMouse.initialize();
	burgerOnMouse.initialize();
	topBar.initialize();
	lowerBar.initialize();
	timeBar.initialize();
	destroyEffect.initialize();
}

void GameScene::update()
{
	computeMatricesFromInputs();

	if (!viewMode)
	{
		if (!drawPath)
		{
			mousePicker->update();
			glm::vec3 v = mousePicker->currentTerrainPoint;
			if (v != glm::vec3{})
			{
				v.y = g_gameScene->terrain->getHeightByPosition(v.x, v.z);
				treeOnMouse.obj.setPosition(v);
			}
		}
		else
		{
			mousePicker->update();
			glm::vec3 v = mousePicker->currentTerrainPoint;
			if (v != glm::vec3{})
			{
				v.y = g_gameScene->terrain->getHeightByPosition(v.x, v.z);
				burgerOnMouse.obj.setPosition(v);
			}
		}
	}
	
	terrain->update();
	sun.update();
	pathManager.update();

	for (auto& v : tree)
		v->update();
	for (auto& v : carAmbo)
		v.update();
	for (auto& v : cloud)
		v.update();
	for (auto& v : streetLight)
		v.update();
	treeOnMouse.update();
	burgerOnMouse.update();
	topBar.update();
	lowerBar.update();
	timeBar.update();
	destroyEffect.update();
}

void GameScene::render()
{
	terrain->render();
	sun.render();
	pathManager.render();
	for (auto& v : tree)
		v->render();
	for (auto& v : carAmbo)
		v.render();
	for (auto& v : cloud)
		v.render();
	for (auto& v : streetLight)
		v.render();
	topBar.render();
	lowerBar.render();
	timeBar.render();
	destroyEffect.render();
	if (!viewMode)
	{
		if (!drawPath)
			treeOnMouse.render();
		else
		{
			burgerOnMouse.render();
		}
	}
}

void GameScene::release()
{
	terrain->release();
	sun.release();
	pathManager.release();
	for (auto& v : tree)
		v->release();
	for (auto& v : carAmbo)
		v.release();
	for (auto& v : cloud)
		v.release();
	for (auto& v : streetLight)
		v.release();
	treeOnMouse.release();
	burgerOnMouse.release();
	topBar.release();
	lowerBar.release();
	timeBar.release();
	destroyEffect.release();
}