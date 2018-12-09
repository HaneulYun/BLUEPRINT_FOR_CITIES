#pragma once
#include "Cloud.h"
#include "StreetLight.h"
#include "Tree.h"
#include "MailBox.h"
#include "Hydrant.h"
#include "Cone.h"

enum Choose {TREE, CLOUD, STREETLIGHT, MAILBOX, HYDRANT, CONE };

class PropManager
{
public:
	std::list<Tree*> tree;
	std::list<StreetLight*> streetLight;
	std::list<Cloud*> cloud;
	std::list<MailBox*> mailbox;
	std::list<Hydrant*> hydrant;
	std::list<Cone*> cone;
	bool drawState{ false };
	Choose chooseProp;

public:
	PropManager();
	~PropManager();

	void initialize();
	void update();
	void render();
	void release();
	void extractDepthmap();

	void inputInitialize();
	void inputProp(Choose prop);
};

