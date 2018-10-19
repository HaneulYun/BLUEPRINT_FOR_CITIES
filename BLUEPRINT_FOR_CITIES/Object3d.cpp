#include <gl/freeglut.h>
#include "Object3d.h"

Object3d::Object3d() : beginMode{}
{
}

Object3d::~Object3d()
{
}

void Object3d::initialize()
{
}

void Object3d::update()
{
}

void Object3d::render()
{
	Object::preRender();

	if (bVisible)
	{
		glBegin(beginMode);
		for (auto& v : vectors)
			glVertex3f(v.x, v.y, v.z);
		glEnd();
	}

	Object::postRender();
}

void Object3d::release()
{
}

void Object3d::setBeginMode(unsigned char mode)
{
	beginMode = mode;
}

unsigned char Object3d::getBeginMode() const
{
	return beginMode;
}