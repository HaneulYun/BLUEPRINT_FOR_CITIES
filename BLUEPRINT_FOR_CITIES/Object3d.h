#pragma once
#include <vector>
#include <gl/glew.h>
#include <glm/glm.hpp>
#include "Object.h"

class Object3d : public Object
{
	std::vector< glm::vec3 > vertices;

	GLuint programID;
	GLuint matrixID;
	GLuint viewMatrixID;
	GLuint modelMatrixID;

	GLuint texture;
	GLuint textureID;

	GLuint lightID;

	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;
public:

	Object3d();
	~Object3d();

	void initialize();
	void update();
	void render();
	void release();
};