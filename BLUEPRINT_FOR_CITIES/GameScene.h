#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Scene.h"

class GameScene : public Scene
{
	std::vector< glm::vec3 > vertices;

	GLuint VertexArrayID;

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
	GameScene();
	~GameScene();

	void initialize();
	void update();
	void render();
	void release();
};