#include "Terrain.h"


Terrain::Terrain()
{
}

Terrain::~Terrain()
{
	release();
}

void Terrain::initialize(int _width, int _length)
{
	Object3d::initialize();
	width = _width;
	length = _length;

	heights = new float*[length];
	for (int i = 0; i < length; ++i)
		heights[i] = new float[width];

	normals = new glm::vec3*[length];
	for (int i = 0; i < length; ++i)
		normals[i] = new glm::vec3[width];

	computedNormals = false;
}

void Terrain::update()
{

}

void Terrain::render()
{

}

void Terrain::release()
{
	for (int i = 0; i < length; i++)
		delete[] heights[i];
	delete[] heights;

	for (int i = 0; i < length; i++)
		delete[] normals[i];
	delete[] normals;
}

void Terrain::computeNormals()
{

}

void Terrain::setHeight(int x, int z, float y)
{
	heights[z][x] = y;
	computedNormals = false;
}

int Terrain::getWidth() const
{
	return width;
}

int Terrain::getLength() const
{
	return length;
}

float Terrain::getHeight(int x, int z) const
{
	return heights[z][x];
}

glm::vec3 Terrain::getNormal(int x, int z) const
{
	return normals[z][x];
}