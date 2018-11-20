#pragma once
#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct TextureIDData
{
	GLuint textureID{ 0 };
	GLuint textureSID{ 0 };
};

class TextureManager
{
	std::map<std::string, TextureIDData> textureDatas;

public:
	TextureIDData loadBMP(const std::string path, GLuint programID);
};