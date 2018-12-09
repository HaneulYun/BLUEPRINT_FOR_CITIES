#include "SelectProp.h"
#include "GameScene.h"

SelectProp::SelectProp()
{
}

SelectProp::~SelectProp()
{
}

void SelectProp::initialize()
{
	mainobj.setBMP("resources/menucolor.bmp");
	mainobj.setOBJ("resources/SM_Env_Tree_02_Internal.obj");
	mainobj.initialize();
	mainobj.setColor(255.f / 255, 137.f / 255, 81.f / 255);
	mainobj.setScale(85.f, 85.f, 1.f);

	subTree.setBMP("resources/menucolor.bmp");
	subTree.setOBJ("resources/SM_Env_Tree_02_Internal.obj");
	subTree.initialize();
	subTree.setColor(255.f / 255, 137.f / 255, 81.f / 255);
	subTree.setScale(85.f, 85.f, 1.f);

	subCloud.setBMP("resources/menucolor.bmp");
	subCloud.setOBJ("resources/SM_Env_Cloud_01_Internal.obj");
	subCloud.initialize();
	subCloud.setColor(255.f / 255, 137.f / 255, 81.f / 255);
	subCloud.setScale(85.f, 85.f, 1.f);

	subStreetlight.setBMP("resources/menucolor.bmp");
	subStreetlight.setOBJ("resources/SM_Prop_LightPole_Base_02_Internal.obj");
	subStreetlight.initialize();
	subStreetlight.setColor(255.f / 255, 137.f / 255, 81.f / 255);
	subStreetlight.setScale(85.f, 85.f, 1.f);

	subMailbox.setBMP("resources/menucolor.bmp");
	subMailbox.setOBJ("resources/SM_Prop_Mailbox_01_Internal.obj");
	subMailbox.initialize();
	subMailbox.setColor(255.f / 255, 137.f / 255, 81.f / 255);
	subMailbox.setScale(85.f, 85.f, 1.f);

	subHydrant.setBMP("resources/menucolor.bmp");
	subHydrant.setOBJ("resources/SM_Prop_Hydrant_01_Internal.obj");
	subHydrant.initialize();
	subHydrant.setColor(255.f / 255, 137.f / 255, 81.f / 255);
	subHydrant.setScale(85.f, 85.f, 1.f);

	subCone.setBMP("resources/menucolor.bmp");
	subCone.setOBJ("resources/SM_Prop_Cone_01_Internal.obj");
	subCone.initialize();
	subCone.setColor(255.f / 255, 137.f / 255, 81.f / 255);
	subCone.setScale(85.f, 85.f, 1.f);

	select = false;
}

void SelectProp::update()
{
	mainobj.update();
	if (g_gameScene->viewMode)
	{
		mainobj.setPosition(0, -1000, 0);
		subTree.setPosition(0, -1000, 0);
		subCloud.setPosition(0, -1000, 0);
		subStreetlight.setPosition(0, -1000, 0);
		subMailbox.setPosition(0, -1000, 0);
		subHydrant.setPosition(0, -1000, 0);
		subCone.setPosition(0, -1000, 0);
	}
	else
	{
		mainobj.setPosition(-450, -412, 0.1f);
		subTree.setPosition(-650, -412, 0.1f);
		subCloud.setPosition(-450, -412, 0.1f);
		subStreetlight.setPosition(-250, -412, 0.1f);
		subMailbox.setPosition(-50, -412, 0.1f);
		subHydrant.setPosition(150, -412, 0.1f);
		subCone.setPosition(350, -412, 0.1f);
	}
}

void SelectProp::render()
{
	if (!select && !g_gameScene->selectRoad.select && !g_gameScene->selectGrid.select) mainobj.render();
	if (select)
	{
		subTree.render();
		subCloud.render();
		subStreetlight.render();
		subMailbox.render();
		subHydrant.render();
		subCone.render();
	}
}

void SelectProp::release()
{
	mainobj.release();
	subTree.release();
	subCloud.release();
	subStreetlight.release();
	subMailbox.release();
	subHydrant.release();
	subCone.release();
}