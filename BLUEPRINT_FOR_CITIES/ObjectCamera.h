#pragma once
#include "Object.h"

class ObjectCamera : public Object
{
	union
	{
		struct
		{
			double eyeX;
			double eyeY;
			double eyeZ;
		};
		Vector3d eye;
	};
	union
	{
		struct
		{
			double atX;
			double atY;
			double atZ;
		};
		Vector3d at;
	};
	union
	{
		struct
		{
			double upX;
			double upY;
			double upZ;
		};
		Vector3d up;
	};
public:
	ObjectCamera();
	~ObjectCamera();

	void initialize();
	void update();
	void preRender();
	void render();
	void release();
};