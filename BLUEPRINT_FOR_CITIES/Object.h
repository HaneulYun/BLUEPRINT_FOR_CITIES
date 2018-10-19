#pragma once
#include <vector>
#include "Vector3.h"
#include "Color3.h"
#include "Matrix3d.h"

class Object
{
protected:
	Vector3	position;
	Vector3	rotation;
	Vector3	scale;
	Color3	color;
	union {
		struct {
			float axisX;
			float axisY;
			float axisZ;
			float rotationAxis;
		};
		Vector3	axis;
	};
	union {
		GLfloat v[16];
		Matrix3d matrix;
	};
public:

	std::vector<Object*> child;
	int hierarchyLevel;

protected:
	bool bVisible;

public:
	Object();
	virtual ~Object();

	virtual void initialize();
	virtual void update();
	virtual void preRender();
	void postRender();
	virtual void render();
	virtual void release();

	void addChild(Object* _child);

	void setVisible(const bool _b);
	void setRotationAxis(const float _r);
	void adjustRotationAxis(const float _r);

	void setPosition(float _x, float _y, float _z);
	void setPosition(const Vector3 _position);

	void setRotation(float _x, float _y, float _z);
	void setRotation(const Vector3 _rotation);

	void setAxis(float _x, float _y, float _z);
	void setAxis(const Vector3 _axis);

	void setScale(float _x, float _y, float _z);
	void setScale(const Vector3 _scale);

	void setColor(float _r, float _g, float _b);
	void setColor(const Vector3 _color);

	Vector3 getPosition() const;
	Vector3 getRotation() const;
	Vector3 getScale() const;
	Vector3 getColor() const;

	void adjustPosition(float _x, float _y, float _z);
	void adjustPosition(const Vector3 _position);

	void adjustRotation(float _x, float _y, float _z);
	void adjustRotation(const Vector3 _rotation);

	void adjustScale(float _x, float _y, float _z);
	void adjustScale(const Vector3 _scale);

	void adjustColor(float _r, float _g, float _b);
	void adjustColor(const Vector3 _color);
};