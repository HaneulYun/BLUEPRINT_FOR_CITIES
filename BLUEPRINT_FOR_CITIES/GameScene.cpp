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
	std::uniform_int_distribution<int> uid_7(0, 6);
	std::uniform_int_distribution<int> uid_360(1, 360);
	std::uniform_int_distribution<int> uid_200(-100, 100);
	std::default_random_engine dre(std::chrono::steady_clock::now().time_since_epoch().count());
	for (int i = 0; i < 10; ++i)
		for (int j = 0; j < 10; ++j)
		{
			obj[i][j].setBMP("resources/T_PolygonCity_Texture_01_A.bmp");
			switch (uid_7(dre)) {
			case 1: obj[i][j].setOBJ("resources/SM_Env_Tree_01_Internal.obj"); break;
			case 2: obj[i][j].setOBJ("resources/SM_Env_Tree_02_Internal.obj"); break;
			default: obj[i][j].setOBJ("resources/SM_Env_Tree_03_Internal.obj"); break;
			}
			obj[i][j].initialize();
			obj[i][j].setPosition(-4.5 + i + uid_200(dre) / 200.f, 0, -4.5 + j + uid_200(dre) / 200.f);
			obj[i][j].setRotation(0, float(uid_360(dre)), 0);
		}
	for (auto& v : chicken)
		v.initialize();
}

void GameScene::update()
{
	computeMatricesFromInputs();
	for (int i = 0; i < 10; ++i)
		for (int j = 0; j < 10; ++j)
			obj[i][j].update();
	for (auto& v : chicken)
		v.update();
}

void GameScene::render()
{
	for (int i = 0; i < 10; ++i)
		for (int j = 0; j < 10; ++j)
			obj[i][j].render();
	for (auto& v : chicken)
		v.render();
}

void GameScene::release()
{
	for (int i = 0; i < 10; ++i)
		for (int j = 0; j < 10; ++j)
			obj[i][j].release();
	for (auto& v : chicken)
		v.release();
}