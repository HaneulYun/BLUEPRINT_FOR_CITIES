#pragma once
#include <vector>
#include <string>
#include <gl/glew.h>
#include <glm/glm.hpp>
#include "Object.h"

class ObjectUI : public Object
{
	MeshIDData meshData;
	TextureIDData textureData;

	GLuint programID;
	GLuint matrixID;
	GLuint viewMatrixID;
	GLuint modelMatrixID;

	GLuint colorID;
	GLuint lightID;

	std::string urlBMP;
	std::string urlOBJ;

public:
	ObjectUI();
	~ObjectUI();

	void initialize();
	void update();
	void render();
	void release();

	void setBMP(std::string _url);
	void setOBJ(std::string _url);
};