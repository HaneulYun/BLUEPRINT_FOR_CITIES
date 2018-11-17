#include "Object.h"
#include <glm/gtx/transform.hpp>

Object::Object()
{
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
	if (!hierarchyLevel)
		mat = glm::mat4(1.f);
	glm::mat4 matTranslation = glm::translate(glm::mat4(), position);
	glm::mat4 matRotation = glm::rotate(rotation.y, glm::vec3{ 0, 1, 0 }) *
		glm::rotate(rotation.z, glm::vec3{ 0, 0, 1 }) * glm::rotate(rotation.x, glm::vec3{ 1, 0, 0 });
	glm::mat4 matScale = glm::scale(scale);

	mat = matTranslation * matRotation * matScale;
}

void Object::postRender()
{
	if(child.size())
		for (auto& v : child)
			if (v) v->render();
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

void Object::setPosition(float _x, float _y, float _z)
{
	position = { _x, _y, _z };
}

void Object::setRotation(float _x, float _y, float _z)
{
	rotation = { _x, _y, _z };
}

void Object::setScale(float _s)
{
	scale = { _s, _s, _s };
}

void Object::setScale(float _x, float _y, float _z)
{
	scale = { _x, _y, _z };
}

void Object::setColor(float _r, float _g, float _b)
{
	if (_r > 1.f) _r = 1.f; else if (_r < 0.f) _r = 0.f;
	if (_g > 1.f) _g = 1.f; else if (_g < 0.f) _g = 0.f;
	if (_b > 1.f) _b = 1.f; else if (_b < 0.f) _b = 0.f;
	color = { _r, _g, _b };
}

void Object::setPosition(const glm::vec3 _position)
{
	position = _position;
}

void Object::setRotation(const glm::vec3 _rotation)
{
	rotation = _rotation;
}

void Object::setScale(const glm::vec3 _scale)
{
	scale = _scale;
}

void Object::setColor(const glm::vec3 _color)
{
	color = _color;
}

glm::vec3 Object::getPosition() const
{
	return position;
}

glm::vec3 Object::getRotation() const
{
	return rotation;
}

glm::vec3 Object::getScale() const
{
	return scale;
}

glm::vec3 Object::getColor() const
{
	return color;
}

bool Object::getVisible() const
{
	return bVisible;
}

void Object::adjustPosition(float _x, float _y, float _z)
{
	position += glm::vec3{ _x, _y, _z };
}

void Object::adjustRotation(float _x, float _y, float _z)
{
	rotation += glm::vec3{ _x, _y, _z };
}

void Object::adjustScale(float _x, float _y, float _z)
{
	scale += glm::vec3{ _x, _y, _z };
}

void Object::adjustColor(float _r, float _g, float _b)
{
	if (color.r += _r; color.r > 1.f) color.r = 1.f;
	if (color.g += _g; color.g > 1.f) color.g = 1.f;
	if (color.b += _b; color.b > 1.f) color.b = 1.f;
}

void Object::adjustPosition(const glm::vec3 _position)
{
	position += _position;
}

void Object::adjustRotation(const glm::vec3 _rotation)
{
	rotation += _rotation;
}

void Object::adjustScale(const glm::vec3 _scale)
{
	scale += _scale;
}

void Object::adjustColor(const glm::vec3 _color)
{
	color += _color;
}