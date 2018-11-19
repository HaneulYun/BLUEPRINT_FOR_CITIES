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
	for (auto& v : babychicken)
		v.initialize();
	for (auto& v : chicken)
		v.initialize();
}

void GameScene::update()
{
	Object3d::radian += 0.001f;
	computeMatricesFromInputs();
	for (auto& v : tree)
		v.update();
	for (auto& v : babychicken)
		v.update();
	for (auto& v : chicken)
		v.update();
}

void GameScene::render()
{
	for (auto& v : tree)
		v.render();
	for (auto& v : babychicken)
		v.render();
	for (auto& v : chicken)
		v.render();
}

void GameScene::release()
{
	for (auto& v : tree)
		v.release();
	for (auto& v : babychicken)
		v.release();
	for (auto& v : chicken)
		v.release();
}