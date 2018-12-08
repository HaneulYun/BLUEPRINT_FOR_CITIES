#include "PropManager.h"
#include "GameScene.h"

PropManager::PropManager()
{
}

PropManager::~PropManager()
{
}

void PropManager::initialize()
{
	tree.resize(100);
	for (auto& v : tree)
	{
		v = new Tree();
		v->initialize();
	}

	streetLight.resize(50);
	for (auto& v : streetLight)
	{
		v = new StreetLight();
		v->initialize();
	}

	cloud.resize(10);
	for (auto& v : cloud)
	{
		v = new Cloud();
		v->initialize();
	}
}

void PropManager::update()
{
	for (auto& v : tree)
		v->update();
	for (auto& v : streetLight)
		v->update();
	for (auto& v : cloud)
		v->update();
}

void PropManager::render()
{
	for (auto& v : tree)
		v->render();
	for (auto& v : streetLight)
		v->render();
	for (auto& v : cloud)
		v->render();
}

void PropManager::release()
{
	for (auto& v : tree)
		v->release();
	for (auto& v : streetLight)
		v->release();
	for (auto& v : cloud)
		v->release();
}

void PropManager::inputInitialize()
{
}

void PropManager::inputProp(Choose prop)
{
	if (prop == TREE)
	{
		tree.push_back(new Tree());
		tree.back()->initialize();
		glm::vec3 v = g_gameScene->mousePicker->currentTerrainPoint;
		if (v != glm::vec3{})
		{
			v.y = g_gameScene->terrain->getHeightByPosition(v.x, v.z);
		}
		tree.back()->obj.setPosition(v);
	}
	else if (prop == CLOUD)
	{
		cloud.push_back(new Cloud());
		cloud.back()->initialize();
		glm::vec3 v = g_gameScene->mousePicker->currentTerrainPoint;
		if (v != glm::vec3{})
		{
			v.y = g_gameScene->terrain->getHeightByPosition(v.x, v.z);
		}
		cloud.back()->obj.setPosition(v);
	}
	else if (prop == STREETLIGHT)
	{
		streetLight.push_back(new StreetLight());
		streetLight.back()->initialize();
		glm::vec3 v = g_gameScene->mousePicker->currentTerrainPoint;
		if (v != glm::vec3{})
		{
			v.y = g_gameScene->terrain->getHeightByPosition(v.x, v.z);
		}
		streetLight.back()->obj.setPosition(v);
	}
}