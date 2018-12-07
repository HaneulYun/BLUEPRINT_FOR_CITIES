#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include "Object3d.h"

class Terrain : public Object3d
{
	int width{ 0 };
	int length{ 0 };
	float** heights{ nullptr };
	glm::vec3** normals{ nullptr };
	bool computedNormals{ false };
	
public:
	Terrain();
	~Terrain();

	void initialize(int _width, int _length);
	void update();
	void render();
	void release();

	void computeNormals();

	void setHeight(int x, int z, float y);

	int getWidth() const;
	int getLength() const;
	float getHeight(int x, int z) const;
	glm::vec3 getNormal(int x, int z) const;
};