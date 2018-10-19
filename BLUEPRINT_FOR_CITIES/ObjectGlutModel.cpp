#include <gl/freeglut.h>
#include "ObjectGlutModel.h"

ObjectGlutModel::ObjectGlutModel() : model{ e_model_none }, solid{ false }
{
}

ObjectGlutModel::~ObjectGlutModel()
{
}

void ObjectGlutModel::initialize()
{
}

void ObjectGlutModel::update()
{
}

void ObjectGlutModel::render()
{
	Object::preRender();

	if (bVisible)
	{
		if(solid)
			switch (model)
			{
			case e_model_type::e_model_cone:
				glutSolidCone(base, height, slices, stacks);
				break;
			case e_model_type::e_model_cube:
				glutSolidCube(size);
				break;
			case e_model_type::e_model_sphere:
				glutSolidSphere(radius, slices, stacks);
				break;
			case e_model_type::e_model_torus:
				glutSolidTorus(innerRadius, outerRadius, nSlides, nRings);
				break;
			case e_model_type::e_model_teapot:
				glutSolidTeapot(size);
				break;
			case e_model_type::e_model_none:
				break;
			}
		else
			switch (model)
			{
			case e_model_type::e_model_cone:
				glutWireCone(base, height, slices, stacks);
				break;
			case e_model_type::e_model_cube:
				glutWireCube(size);
				break;
			case e_model_type::e_model_sphere:
				glutWireSphere(radius, slices, stacks);
				break;
			case e_model_type::e_model_torus:
				glutWireTorus(innerRadius, outerRadius, nSlides, nRings);
				break;
			case e_model_type::e_model_teapot:
				glutWireTeapot(size);
				break;
			case e_model_type::e_model_none:
				break;
			}
	}

	Object::postRender();
}

void ObjectGlutModel::release()
{
}

void ObjectGlutModel::setSolid(const bool _b)
{
	solid = _b;
}

void ObjectGlutModel::setModelCone(double _base, double _height, int _slices, int _stacks)
{
	model = e_model_cone;
	base = _base;
	height = _height;
	slices = _slices;
	stacks = _stacks;
}

void ObjectGlutModel::setModelCube(double _size)
{
	model = e_model_cube;
	size = _size;
}

void ObjectGlutModel::setModelSphere(double _radius, int _slices, int _stacks)
{
	model = e_model_sphere;
	radius = _radius;
	slices = _slices;
	stacks = _stacks;
}

void ObjectGlutModel::setModelTorus(double _innerRadius, double _outerRadius, int _nSlides, int _nRings)
{
	model = e_model_torus;
	innerRadius = _innerRadius;
	outerRadius = _outerRadius;
	nSlides = _nSlides;
	nRings = _nRings;
}

void ObjectGlutModel::setModelTeapot(double _size)
{
	model = e_model_teapot;
	size = _size;
}