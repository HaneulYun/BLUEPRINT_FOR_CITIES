#include <random>
#include <chrono>

#include "GameScene.h"
#include "controls.hpp"

float Object3d::radian = 0;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::initialize()
{
	for (auto& v : tree)
		v.initialize();
}

void GameScene::update()
{
	Object3d::radian += 0.01f;
	computeMatricesFromInputs();
	for (auto& v : tree)
		v.update();
}

void GameScene::render()
{
	for (auto& v : tree)
		v.render();
}

void GameScene::release()
{
	for (auto& v : tree)
		v.release();
}