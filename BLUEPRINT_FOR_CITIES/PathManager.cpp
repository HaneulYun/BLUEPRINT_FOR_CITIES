#include "PathManager.h"
#include "GameScene.h"

PathManager::PathManager()
{
}

PathManager::~PathManager()
{
}

void PathManager::initialize()
{
	builder.initialize();
}

void PathManager::update()
{
	
}

void PathManager::render()
{
	for (auto& v : node)
		v->render();
	for (auto& v : segment)
		v->render();
}

void PathManager::release()
{
}

void PathManager::extractDepthmap()
{
	if (drawRoadState)
		builder.obj.extractDepthmap();
	for (auto& v : node)
		v->obj.extractDepthmap();
	for (auto& v : segment)
		v->obj.extractDepthmap();
}

void PathManager::inputInitialize()
{
	builder.initialize();
}

void PathManager::inputNode(Node* _node)
{
	if (!builder.node[0])
		builder.node[0] = _node;
	else if (!builder.node[1] && drawMode)
		builder.node[1] = _node;
	else if (!builder.node[2])
		builder.node[2] = _node;

	if (builder.node[2])
	{
		float t;
		int stack = 1;
		float offset = 0.25f;
		node.push_back(builder.node[0]);
		if (!drawMode)
		{
			float distance = glm::distance(builder.node[2]->getPosition() - builder.node[0]->getPosition(), {});

			stack = distance / offset;

			for (int i = 0; i < stack; ++i)
			{
				t = float(i + 1) / (stack + 1);
				Node* newNode = new Node();
				newNode->initialize();
				glm::vec3 v = (1 - t) * builder.node[0]->getPosition() + t * builder.node[2]->getPosition();
				v.y = g_gameScene->terrain->getHeightByPosition(v.x, v.z);
				newNode->obj.setPosition(v);
				node.push_back(newNode);
			}
		}
		else
		{
			glm::vec3 residualDistance = (builder.node[2]->getPosition() - builder.node[0]->getPosition());
			float distance = glm::distance(builder.node[0]->getPosition(), builder.node[1]->getPosition()) +
				glm::distance(builder.node[1]->getPosition(), builder.node[2]->getPosition());

			stack = distance / offset;


			for (int i = 0; i < stack; ++i)
			{
				t = float(i + 1) / (stack + 1);
				Node* newNode = new Node();
				newNode->initialize();
				glm::vec3 v = (1-t) * ((1 - t) * builder.node[0]->getPosition() + t * builder.node[1]->getPosition())
					+ t * ((1 - t) * builder.node[1]->getPosition() + t * builder.node[2]->getPosition());
				v.y = g_gameScene->terrain->getHeightByPosition(v.x, v.z);
				newNode->obj.setPosition(v);
				node.push_back(newNode);
			}
		}
		node.push_back(builder.node[2]);

		builder.initialize();
		builder.node[0] = _node;
	}
}