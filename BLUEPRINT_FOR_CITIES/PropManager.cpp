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

	mailbox.resize(10);
	for (auto& v : mailbox)
	{
		v = new MailBox();
		v->initialize();
	}

	hydrant.resize(10);
	for (auto& v : hydrant)
	{
		v = new Hydrant();
		v->initialize();
	}

	cone.resize(10);
	for (auto& v : cone)
	{
		v = new Cone();
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
	for (auto& v : mailbox)
		v->update();
	for (auto& v : hydrant)
		v->update();
	for (auto& v : cone)
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
	for (auto& v : mailbox)
		v->render();
	for (auto& v : hydrant)
		v->render();
	for (auto& v : cone)
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
	for (auto& v : mailbox)
		v->release();
	for (auto& v : hydrant)
		v->release();
	for (auto& v : cone)
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
			v.y = g_gameScene->terrain->getHeightByPosition(v.x, v.z) + 4.f;
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
	else if (prop == MAILBOX)
	{
		mailbox.push_back(new MailBox());
		mailbox.back()->initialize();
		glm::vec3 v = g_gameScene->mousePicker->currentTerrainPoint;
		if (v != glm::vec3{})
		{
			v.y = g_gameScene->terrain->getHeightByPosition(v.x, v.z);
		}
		mailbox.back()->obj.setPosition(v);
	}
	else if (prop == HYDRANT)
	{
		hydrant.push_back(new Hydrant());
		hydrant.back()->initialize();
		glm::vec3 v = g_gameScene->mousePicker->currentTerrainPoint;
		if (v != glm::vec3{})
		{
			v.y = g_gameScene->terrain->getHeightByPosition(v.x, v.z);
		}
		hydrant.back()->obj.setPosition(v);
	}
	else if (prop == CONE)
	{
		cone.push_back(new Cone());
		cone.back()->initialize();
		glm::vec3 v = g_gameScene->mousePicker->currentTerrainPoint;
		if (v != glm::vec3{})
		{
			v.y = g_gameScene->terrain->getHeightByPosition(v.x, v.z);
		}
		cone.back()->obj.setPosition(v);
	}
}