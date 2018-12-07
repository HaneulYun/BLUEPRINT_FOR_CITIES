#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include "Object.h"

struct Image
{
	int width;
	int height;
	char** pixels;
};

class Terrain : public Object
{
	GLuint vertexbufferID;
	GLuint normalbufferID;
	unsigned int verticesSize;

	GLuint programID;
	GLuint matrixID;
	GLuint viewMatrixID;
	GLuint modelMatrixID;

	GLuint lightID;

	float terrainWidth;
	float terrainLength;

	bool computedNormals{ false };

public:
	int width{ 0 };
	int length{ 0 };
	float** heights{ nullptr };
	glm::vec3** normals{ nullptr };
	
public:
	Terrain();
	~Terrain();


	void initialize();
	void update();
	void render();
	void release();

	void setTerrainSize(int _width, int _length);
	void setSize(int _width, int _length);
	Image* loadBMP(std::string path);
	void loadTerrain(std::string path, float height);

	void computeNormals();

	void setHeight(int x, int z, float y);

	int getWidth() const;
	int getLength() const;
	float getHeight(int x, int z) const;
	float getHeightByPosition(float x, float z) const;
	glm::vec3 getNormal(int x, int z) const;
};