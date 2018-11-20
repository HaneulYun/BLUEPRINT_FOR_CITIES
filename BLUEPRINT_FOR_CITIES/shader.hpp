#pragma once
#include <map>
#include <GL/glew.h>

class ShaderManager
{
	std::map<std::pair<std::string, std::string>, GLuint> programDatas;

public:
	GLuint loadShaders(const std::string vertex_path, const std::string fragment_path);
};