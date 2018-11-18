#pragma once
#include <random>
#include <chrono>
#include "Scene.h"
#include "Object3d.h"

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
		obj.setScale(2.5);
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
	Chicken chicken[100];
public:
	GameScene();
	~GameScene();

	void initialize();
	void update();
	void render();
	void release();
};