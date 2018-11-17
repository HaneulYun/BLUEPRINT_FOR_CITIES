#pragma once

class Scene
{
protected:
	float viewportWidth;
	float viewportHeight;
public:
	Scene();
	virtual ~Scene();

	virtual void initialize();
	virtual void update();
	virtual void render();
	virtual void release();
};