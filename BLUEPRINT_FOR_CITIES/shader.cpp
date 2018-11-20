#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#include <stdlib.h>

#include "shader.hpp"

GLuint ShaderManager::loadShaders(const std::string vertex_path, const std::string fragment_path)
{
	auto iter = programDatas.find(std::pair<std::string, std::string>(vertex_path, fragment_path));
	if (iter == programDatas.end())
	{
		GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		std::string VertexShaderCode;
		std::ifstream VertexShaderStream(vertex_path.c_str(), std::ios::in);
		if (VertexShaderStream.is_open())
		{
			std::string Line = "";
			while (getline(VertexShaderStream, Line))
				VertexShaderCode += "\n" + Line;
			VertexShaderStream.close();
		}
		else
		{
			printf("Impossible to open %s.\n", vertex_path.c_str());
			getchar();
			return {};
		}

		std::string FragmentShaderCode;
		std::ifstream FragmentShaderStream(fragment_path.c_str(), std::ios::in);
		if (FragmentShaderStream.is_open())
		{
			std::string Line = "";
			while (getline(FragmentShaderStream, Line))
				FragmentShaderCode += "\n" + Line;
			FragmentShaderStream.close();
		}

		GLint Result = GL_FALSE;
		int InfoLogLength;


		printf("Compiling shader : %s\n", vertex_path.c_str());
		char const * VertexSourcePointer = VertexShaderCode.c_str();
		glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
		glCompileShader(VertexShaderID);

		glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0)
		{
			std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
			printf("%s\n", &VertexShaderErrorMessage[0]);
		}



		printf("Compiling shader : %s\n", fragment_path.c_str());
		char const * FragmentSourcePointer = FragmentShaderCode.c_str();
		glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
		glCompileShader(FragmentShaderID);

		glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0)
		{
			std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
			printf("%s\n", &FragmentShaderErrorMessage[0]);
		}

		programDatas.insert(std::pair<std::pair<std::string, std::string>, GLuint>(std::pair<std::string, std::string>(vertex_path, fragment_path), {}));

		printf("Linking program\n");
		programDatas[std::pair<std::string, std::string>(vertex_path, fragment_path)] = glCreateProgram();
		glAttachShader(programDatas[std::pair<std::string, std::string>(vertex_path, fragment_path)], VertexShaderID);
		glAttachShader(programDatas[std::pair<std::string, std::string>(vertex_path, fragment_path)], FragmentShaderID);
		glLinkProgram(programDatas[std::pair<std::string, std::string>(vertex_path, fragment_path)]);

		glGetProgramiv(programDatas[std::pair<std::string, std::string>(vertex_path, fragment_path)], GL_LINK_STATUS, &Result);
		glGetProgramiv(programDatas[std::pair<std::string, std::string>(vertex_path, fragment_path)], GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0)
		{
			std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
			glGetProgramInfoLog(programDatas[std::pair<std::string, std::string>(vertex_path, fragment_path)], InfoLogLength, NULL, &ProgramErrorMessage[0]);
			printf("%s\n", &ProgramErrorMessage[0]);
		}

		glDetachShader(programDatas[std::pair<std::string, std::string>(vertex_path, fragment_path)], VertexShaderID);
		glDetachShader(programDatas[std::pair<std::string, std::string>(vertex_path, fragment_path)], FragmentShaderID);

		glDeleteShader(VertexShaderID);
		glDeleteShader(FragmentShaderID);
	}
	return programDatas[std::pair<std::string, std::string>(vertex_path, fragment_path)];
}
