#pragma once
#include <map>
#include <glm/glm.hpp>
#include <gl/glew.h>

bool loadOBJ(
	const char * path, 
	std::vector<glm::vec3> & out_vertices, 
	std::vector<glm::vec2> & out_uvs, 
	std::vector<glm::vec3> & out_normals
);

struct MeshIDData
{
	unsigned int verticesSize{ 0 };
	GLuint vertexbufferID{ 0 };
	GLuint uvbufferID{ 0 };
	GLuint normalbufferID{ 0 };
};

class MeshManager
{
	std::map<std::string, MeshIDData> meshDatas;

public:
	MeshIDData loadOBJ(const std::string path);
};