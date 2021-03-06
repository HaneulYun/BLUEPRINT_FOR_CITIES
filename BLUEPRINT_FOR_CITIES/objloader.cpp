#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>

#include "objloader.hpp"

MeshIDData MeshManager::loadOBJ(const std::string path)
{
	float maxDistance = 0;
	auto iter = meshDatas.find(path);
	if (iter == meshDatas.end())
	{
		printf("Loading OBJ file %s...!!\n", path.c_str());

		std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
		std::vector<glm::vec3> temp_vertices;
		std::vector<glm::vec2> temp_uvs;
		std::vector<glm::vec3> temp_normals;

		std::vector<glm::vec3> out_vertices;
		std::vector<glm::vec2> out_uvs;
		std::vector<glm::vec3> out_normals;


		FILE * file = fopen(path.c_str(), "r");
		if (file == NULL) {
			printf("Impossible to open the file!\n");
			getchar();
			return {};
		}

		while (1) {
			char lineHeader[128];

			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF)
				break;

			if (strcmp(lineHeader, "v") == 0)
			{
				glm::vec3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				temp_vertices.push_back(vertex);
				if (maxDistance < glm::abs(vertex.x))
					maxDistance = glm::abs(vertex.x);
				if (maxDistance < glm::abs(vertex.y))
					maxDistance = glm::abs(vertex.y);
				if (maxDistance < glm::abs(vertex.z))
					maxDistance = glm::abs(vertex.z);
			}
			else if (strcmp(lineHeader, "vt") == 0)
			{
				glm::vec2 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y);
				uv.y = -uv.y;
				temp_uvs.push_back(uv);
			}
			else if (strcmp(lineHeader, "vn") == 0)
			{
				glm::vec3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				temp_normals.push_back(normal);
			}
			else if (strcmp(lineHeader, "f") == 0)
			{
				std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				if (matches != 9) {
					printf("File can't be read\n");
				}
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
			else
			{
				char stupidBuffer[1000];
				fgets(stupidBuffer, 1000, file);
			}
		}

		for (unsigned int i = 0; i < vertexIndices.size(); i++)
		{
			unsigned int vertexIndex = vertexIndices[i];
			unsigned int uvIndex = uvIndices[i];
			unsigned int normalIndex = normalIndices[i];

			glm::vec3 vertex = temp_vertices[vertexIndex - 1];
			glm::vec2 uv = temp_uvs[uvIndex - 1];
			uv.y = 1 - uv.y;
			glm::vec3 normal = temp_normals[normalIndex - 1];

			out_vertices.push_back(vertex);
			out_uvs.push_back(uv);
			out_normals.push_back(normal);
		}

		for (auto& v : out_vertices)
			v /= maxDistance;

		meshDatas.insert(std::pair<std::string, MeshIDData>(path, {out_vertices.size(), 0, 0, 0}));
		meshDatas[path].scale = 1 / maxDistance;

		glGenBuffers(1, &meshDatas[path].vertexbufferID);
		glBindBuffer(GL_ARRAY_BUFFER, meshDatas[path].vertexbufferID);
		glBufferData(GL_ARRAY_BUFFER, out_vertices.size() * sizeof(glm::vec3), &out_vertices[0], GL_STATIC_DRAW);

		glGenBuffers(1, &meshDatas[path].uvbufferID);
		glBindBuffer(GL_ARRAY_BUFFER, meshDatas[path].uvbufferID);
		glBufferData(GL_ARRAY_BUFFER, out_uvs.size() * sizeof(glm::vec2), &out_uvs[0], GL_STATIC_DRAW);

		glGenBuffers(1, &meshDatas[path].normalbufferID);
		glBindBuffer(GL_ARRAY_BUFFER, meshDatas[path].normalbufferID);
		glBufferData(GL_ARRAY_BUFFER, out_normals.size() * sizeof(glm::vec3), &out_normals[0], GL_STATIC_DRAW);
	}
	return meshDatas[path];
}