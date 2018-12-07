#include <random>
#include <chrono>

#include "GameScene.h"
#include "controls.hpp"

GameScene* GameScene::m_instance = nullptr;

float Object::radian = 0;

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
	terrain.loadTerrain("resources\\map.bmp", 3);
	for (auto& v : tree)
		v.initialize();
	topBar.initialize();
	lowerBar.initialize();
}

void GameScene::update()
{
	Object::radian += 0.01f;
	computeMatricesFromInputs();
	terrain.update();
	for (auto& v : tree)
		v.update();
	topBar.update();
	lowerBar.update();
}

void GameScene::render()
{
	terrain.render();
	for (auto& v : tree)
		v.render();
	topBar.render();
	lowerBar.render();
}

void GameScene::release()
{
	terrain.release();
	for (auto& v : tree)
		v.release();
	topBar.release();
	lowerBar.release();
}