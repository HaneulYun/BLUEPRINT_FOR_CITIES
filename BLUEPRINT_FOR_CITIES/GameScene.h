#pragma once
#include <random>
#include <chrono>
#include "Scene.h"
#include "Object3d.h"

class Tree
{
	Object3d obj;
public:

	void initialize()
	{
		std::uniform_int_distribution<int> uid_7(0, 6);
		std::uniform_int_distribution<int> uid_360(1, 360);
		std::uniform_int_distribution<int> uid_200(-100, 100);
		std::default_random_engine dre(std::chrono::steady_clock::now().time_since_epoch().count());

		obj.setBMP("resources/T_PolygonCity_Texture_01_A.bmp");
		switch (uid_7(dre)) {
		case 1: obj.setOBJ("resources/SM_Env_Tree_01_Internal.obj"); break;
		case 2: obj.setOBJ("resources/SM_Env_Tree_02_Internal.obj"); break;
		default: obj.setOBJ("resources/SM_Env_Tree_03_Internal.obj"); break;
		}
		obj.initialize();
		obj.setPosition(uid_200(dre) / 20.f, 0, uid_200(dre) / 20.f);
		obj.setRotation(0, float(uid_360(dre)), 0);

	}
	void update()
	{
		obj.update();
	}
	void render()
	{
		obj.render();
	}
	void release()
	{
		obj.release();
	}
};

class Hamburger
{
	Object3d obj;
public:

	void initialize()
	{
		static std::uniform_int_distribution<int> uid_360(1, 360);
		static std::uniform_int_distribution<int> uid_200(-100, 100);
		static std::default_random_engine dre(std::chrono::steady_clock::now().time_since_epoch().count());

		obj.setBMP("resources/chicken.bmp");
		obj.setOBJ("resources/SM_Prop_LargeSign_Burger_01_Internal.obj");
		obj.initialize();
		obj.setPosition(uid_200(dre) / 20.f, 0, uid_200(dre) / 20.f);
		obj.setRotation(0, float(uid_360(dre)), 0);
		obj.setScale(2 + uid_200(dre) / 200.f);
	}
	void update()
	{
		obj.update();
	}
	void render()
	{
		obj.render();
	}
	void release()
	{
		obj.release();
	}
};

class Chicken
{
	Object3d obj;
public:

	void initialize()
	{
		static std::uniform_int_distribution<int> uid_360(1, 360);
		static std::uniform_int_distribution<int> uid_200(-100, 100);
		static std::default_random_engine dre(std::chrono::steady_clock::now().time_since_epoch().count());
		
		obj.setBMP("resources/chicken.bmp");
		obj.setOBJ("resources/chicken.obj");
		obj.initialize();
		obj.setPosition(uid_200(dre) / 20.f, 0, uid_200(dre) / 20.f);
		obj.setRotation(0, float(uid_360(dre)), 0);
		obj.setScale(2 + uid_200(dre) / 200.f);
	}
	void update()
	{
		obj.update();
	}
	void render()
	{
		obj.render();
	}
	void release()
	{
		obj.release();
	}
};

class BabyChicken
{
	Object3d obj;
public:

	void initialize()
	{
		static std::uniform_int_distribution<int> uid_360(1, 360);
		static std::uniform_int_distribution<int> uid_200(-100, 100);
		static std::default_random_engine dre(std::chrono::steady_clock::now().time_since_epoch().count());

		obj.setBMP("resources/chickenbaby.bmp");
		obj.setOBJ("resources/chickenbaby.obj");
		obj.initialize();
		obj.setPosition(uid_200(dre) / 20.f, 0, uid_200(dre) / 20.f);
		obj.setRotation(0, float(uid_360(dre)), 0);
		obj.setScale(1 + uid_200(dre) / 200.f);
	}
	void update()
	{
		obj.update();
	}
	void render()
	{
		obj.render();
	}
	void release()
	{
		obj.release();
	}
};

class GameScene : public Scene
{
	Object3d obj[10][10];
	Tree tree[100];
	Chicken chicken[30];
	BabyChicken babychicken[50];
public:
	GameScene();
	~GameScene();

	void initialize();
	void update();
	void render();
	void release();
};