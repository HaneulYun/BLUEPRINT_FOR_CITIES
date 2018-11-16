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

	virtual void drawScene(void);
	virtual void reshape(int w, int h);
	virtual void keyboard(unsigned char key, int x, int y);
	virtual void special(int key, int x, int y);
	virtual void mouse(int button, int state, int x, int y);
	virtual void motion(int x, int y);
	virtual void menuFunc(int button);
	virtual void timerFunction(int value);
};