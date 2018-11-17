#include <random>
#include <chrono>

#include "GameScene.h"
#include "controls.hpp"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::initialize()
{
	std::uniform_int_distribution<int> uid_360(1, 360);
	std::uniform_int_distribution<int> uid_200(-100, 100);
	std::default_random_engine dre(std::chrono::steady_clock::now().time_since_epoch().count());
	for (int i = 0; i < 10; ++i)
		for (int j = 0; j < 10; ++j)
		{
			obj[i][j].initialize();
			obj[i][j].setPosition(-4.5 + i + uid_200(dre) / 200.f, 0, -4.5 + j + uid_200(dre) / 200.f);
			obj[i][j].setRotation(0, float(uid_360(dre)), 0);
		}
}

void GameScene::update()
{
	computeMatricesFromInputs();
	for (int i = 0; i < 10; ++i)
		for (int j = 0; j < 10; ++j)
			obj[i][j].update();
}

void GameScene::render()
{
	for (int i = 0; i < 10; ++i)
		for (int j = 0; j < 10; ++j)
			obj[i][j].render();
}

void GameScene::release()
{
	for (int i = 0; i < 10; ++i)
		for (int j = 0; j < 10; ++j)
			obj[i][j].release();
}