#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::initialize()
{
	object.initialize();
}

void GameScene::update()
{
	object.update();
}

void GameScene::render()
{
	object.render();
}

void GameScene::release()
{
	object.release();
}