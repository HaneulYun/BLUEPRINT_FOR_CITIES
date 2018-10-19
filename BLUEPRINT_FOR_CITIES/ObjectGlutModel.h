#pragma once
#include "Object.h"

enum e_model_type
{
	e_model_none,
	e_model_cone,
	e_model_cube,
	e_model_sphere,
	e_model_torus,
	e_model_teapot,

	e_model_num,
};

class ObjectGlutModel : public Object
{
	bool solid;

	e_model_type model;
	union
	{
		double size;			// coube, teapot
		double radius;			// sphere
		struct
		{
			double base;
			double height;
			int slices;			// sphere
			int stacks;			// sphere
		};						// cone
		struct
		{
			double innerRadius;
			double outerRadius;
			int nSlides;
			int nRings;
		};						// torus
	};

public:
	ObjectGlutModel();
	~ObjectGlutModel();

	void initialize();
	void update();
	void render();
	void release();

	void setSolid(const bool _b);

	void setModelCone(double _base, double _height, int _slices, int _stacks);
	void setModelCube(double _size);
	void setModelSphere(double _radius, int _slices, int _stacks);
	void setModelTorus(double _innerRadius, double _outerRadius, int _nSlides, int _nRings);
	void setModelTeapot(double _size);
};