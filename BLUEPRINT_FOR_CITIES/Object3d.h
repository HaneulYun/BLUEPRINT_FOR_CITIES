#pragma once
#include <vector>
#include <string>
#include <gl/glew.h>
#include <glm/glm.hpp>
#include "Object.h"
#include "objloader.hpp"

class Object3d : public Object
{
	static MeshManager manager;

	MeshIDData meshData;

	GLuint programID;
	GLuint matrixID;
	GLuint viewMatrixID;
	GLuint modelMatrixID;

	GLuint texture;
	GLuint textureID;

	GLuint lightID;

	std::string urlBMP;
	std::string urlOBJ;


public:
	static float radian;

	Object3d();
	~Object3d();

	void initialize();
	void update();
	void render();
	void release();

	void setBMP(std::string _url);
	void setOBJ(std::string _url);
};