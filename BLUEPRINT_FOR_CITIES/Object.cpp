#include <gl/freeglut.h>
#include "Object.h"

Object::Object() : position{}, rotation{}, axis{}, scale({ 1, 1, 1 }), color{ 1, 1, 1 },
	bVisible{ true }, matrix{}, hierarchyLevel{ 0 }
{
	rotationAxis = 0.f;
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, v);
}

Object::~Object()
{
}

void Object::initialize()
{
}

void Object::update()
{
	if (child.size())
		for (auto& v : child)
			if (v) v->update();
}

void Object::preRender()
{
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	if (!hierarchyLevel)
		glLoadIdentity();
	glTranslatef(position.x, position.y, position.z);
	glRotatef(rotation.z, 0, 0, 1);
	glRotatef(rotation.y, 0, 1, 0);
	glRotatef(rotation.x, 1, 0, 0);
	glMultMatrixf(v);
	if (axisX != 0 && axisY != 0 && axisZ != 0)
		glRotatef(rotationAxis, axisX, axisY, axisZ);
	glScalef(scale.x, scale.y, scale.z);
	glColor3f(color.r, color.g, color.b);
}

void Object::postRender()
{
	if(child.size())
		for (auto& v : child)
			if (v) v->render();
	glPopMatrix();
}

void Object::render()
{
	preRender();
	postRender();
}

void Object::release()
{
}

void Object::addChild(Object* _child)
{
	_child->hierarchyLevel = hierarchyLevel + 1;
	child.push_back(_child);
}

void Object::deleteChild(Object* _child)
{
	child.remove(_child);
}

void Object::setVisible(const bool _b)
{
	bVisible = _b;
}

void Object::setRotationAxis(const float _r)
{
	rotationAxis = _r;
}

void Object::adjustRotationAxis(const float _r)
{
	rotationAxis += _r;
}

void Object::setPosition(float _x, float _y, float _z)
{
	position = Vector3{ _x, _y, _z };
}

void Object::setRotation(float _x, float _y, float _z)
{
	rotation = Vector3{ _x, _y, _z };
}

void Object::setAxis(float _x, float _y, float _z)
{
	axis = Vector3{ _x, _y, _z };
}

void Object::setScale(float _s)
{
	scale = Vector3{ _s, _s, _s };
}

void Object::setScale(float _x, float _y, float _z)
{
	scale = Vector3{ _x, _y, _z };
}

void Object::setColor(float _r, float _g, float _b)
{
	if (_r > 1.f) _r = 1.f; else if (_r < 0.f) _r = 0.f;
	if (_g > 1.f) _g = 1.f; else if (_g < 0.f) _g = 0.f;
	if (_b > 1.f) _b = 1.f; else if (_b < 0.f) _b = 0.f;
	color = Vector3{ _r, _g, _b };
}

void Object::setPosition(const Vector3 _position)
{
	position = _position;
}

void Object::setRotation(const Vector3 _rotation)
{
	rotation = _rotation;
}

void Object::setAxis(const Vector3 _axis)
{
	axis = _axis;
}

void Object::setScale(const Vector3 _scale)
{
	scale = _scale;
}

void Object::setColor(const Vector3 _color)
{
	color = _color;
}

Vector3 Object::getPosition() const
{
	return position;
}

Vector3 Object::getRotation() const
{
	return rotation;
}

Vector3 Object::getScale() const
{
	return scale;
}

Vector3 Object::getColor() const
{
	return color;
}

bool Object::getVisible() const
{
	return bVisible;
}

void Object::adjustPosition(float _x, float _y, float _z)
{
	position += Vector3{ _x, _y, _z };
}

void Object::adjustRotation(float _x, float _y, float _z)
{
	rotation += Vector3{ _x, _y, _z };
}

void Object::adjustScale(float _x, float _y, float _z)
{
	scale += Vector3{ _x, _y, _z };
}

void Object::adjustColor(float _r, float _g, float _b)
{
	if (color.r += _r; color.r > 1.f) color.r = 1.f;
	if (color.g += _g; color.g > 1.f) color.g = 1.f;
	if (color.b += _b; color.b > 1.f) color.b = 1.f;
}

void Object::adjustPosition(const Vector3 _position)
{
	position += _position;
}

void Object::adjustRotation(const Vector3 _rotation)
{
	rotation += _rotation;
}

void Object::adjustScale(const Vector3 _scale)
{
	scale += _scale;
}

void Object::adjustColor(const Vector3 _color)
{
	color += _color;
}