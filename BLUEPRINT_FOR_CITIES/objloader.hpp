#pragma once
#include <map>
#include <glm/glm.hpp>
#include <gl/glew.h>

struct MeshIDData
{
	unsigned int verticesSize{ 0 };
	GLuint vertexbufferID{ 0 };
	GLuint uvbufferID{ 0 };
	GLuint normalbufferID{ 0 };

	float scale{ 1 };
};

class MeshManager
{
	std::map<std::string, MeshIDData> meshDatas;

public:
	MeshIDData loadOBJ(const std::string path);
};